#include "../includes/minishell.h"

void	ft_executer_error(char **cmd, char *s, int exit_code)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	if (cmd && cmd[0])
		write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": ", 2);
	if (s)
		write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(exit_code);
}