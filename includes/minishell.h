#ifndef MINISHELL_H
# define MINISHELL_H

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

/* ************************************************************************** */
/*                               DEFINES                                      */
/* ************************************************************************** */

# define PROMPT "minishell$ "
# define MAX_PATH 1024

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

// Global variable for signal handling (only one allowed)
extern int g_signal;


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

#endif