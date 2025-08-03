#include "minishell.h"

// Global variable for signal handling (only one allowed by subject)
int g_signal = 0;

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
 * Setup signal handlers
 */
void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

/**
 * Main loop of the shell
 */
void	shell_loop(void)
{
	char	*input;

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
		// For now, just echo the input
		printf("You entered: %s\n", input);
		// Check for exit command
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
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