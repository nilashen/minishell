
#include "minishell.h"

// Global variable for signal handling (only one allowed by subject)
int g_signal = 0;

// Global variable for last exit status (for $?)
int g_last_exit_status = 0;

/**
 * Simple utility function to write string to file descriptor
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return;
	write(fd, s, strlen(s));
}

/**
 * Simple utility function to write string + newline to file descriptor
 */
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/**
 * Signal handler for SIGINT (Ctrl-C)
 */
void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * Signal handler for SIGQUIT (Ctrl-\)
 */
void	sigquit_handler(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
	// Do nothing for Ctrl-\ in interactive mode
}

/**
 * Setup signal handlers for interactive mode
 */
void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	// Setup SIGINT (Ctrl-C) handler
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	// Setup SIGQUIT (Ctrl-\) handler - ignore it completely
	sa_quit.sa_handler = SIG_IGN;  // Ignore the signal completely
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Main loop of the shell
 */
void	shell_loop(void)
{
	char	*input;
	t_cmd	*cmd;

	while (1)
	{
		input = read_input();
		
		// Handle Ctrl-D (EOF)
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break;
		}
		
		// Skip empty input
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		
		// Add to history
		add_history(input);
		
		// Parse the command
		cmd = parse_command(input);
		if (cmd)
		{
			// Execute the command (built-in or external)
			g_last_exit_status = execute_command(cmd);
			free_command(cmd);
		}
		
		free(input);
	}
}

/**
 * Main function
 */
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	// Setup signal handlers
	setup_signals();
	
	// Display welcome message
	ft_putendl_fd("Welcome to Minishell!", STDOUT_FILENO);
	ft_putendl_fd("Type 'exit' to quit.", STDOUT_FILENO);
	
	// Start the main shell loop
	shell_loop();
	
	// Cleanup
	rl_clear_history();
	
	return (0);
}