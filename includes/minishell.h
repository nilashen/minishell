#ifndef MINISHELL_H
# define MINISHELL_H

/*                               INCLUDES                                     */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

// External environ variable
extern char **environ;

/*                               DEFINES                                      */

# define PROMPT "minishell$ "
# define MAX_PATH 1024

/*                               STRUCTURES                                   */

// Simple command structure
typedef struct s_cmd
{
	char	**args;		// Array of arguments (args[0] is the command)
	int		argc;		// Number of arguments
}	t_cmd;

// Global variable for signal handling (only one allowed)
extern int g_signal;

/*                               FUNCTION PROTOTYPES                         */

// Main functions
int		main(int argc, char **argv, char **envp);

// Prompt functions
void	display_prompt(void);
char	*read_input(void);

// Signal functions
void	setup_signals(void);

// Utility functions
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

// Parsing functions
t_cmd	*parse_command(char *input);
void	free_command(t_cmd *cmd);
char	**split_input(char *input);
int		count_words(char *input);

// Execution functions
int		execute_command(t_cmd *cmd);
char	*find_command_path(char *cmd);

#endif