#include "minishell.h"

/**
 * Display the shell prompt
 */
void	display_prompt(void)
{
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
}

/**
 * Read input from user using readline
 * Returns: allocated string with user input, or NULL on EOF (Ctrl-D)
 */
char	*read_input(void)
{
	char	*input;

	input = readline(PROMPT);
	return (input);
}