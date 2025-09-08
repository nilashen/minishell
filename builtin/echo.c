#include "../includes/minishell.h"

// int	ft_flag_check(char **cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	while (cmd[i])
// 	{
// 		j = 0;
// 		if (cmd[i][j] != '-')
// 			return (i);
// 		if (cmd[i][j] == '-' && cmd[i][j + 1] == '\0')
// 			return (i);
// 		while (cmd[i][++j])
// 		{
// 			if (cmd[i][j] != 'n')
// 				return (i);
// 		}
// 		i++;
// 	}
// 	return (i);
// }

static int	ft_parse_echo_flags(char **cmd, int *no_newline)
{
	int	index;
	int	j;

	index = 1;
	*no_newline = 0;
	while (cmd[index] && cmd[index][0] == '-' && cmd[index][1] == 'n')
	{
		j = 1;
		while (cmd[index][j] == 'n')
			j++;
		if (cmd[index][j] == '\0')
		{
			*no_newline = 1;
			index++;
		}
		else
			break ;
	}
	return (index);
}

static void	ft_print_echo_args(char **cmd, int index, int fd)
{
	while (cmd[index])
	{
		write(fd, cmd[index], ft_strlen(cmd[index]));
		if (cmd[index + 1] != NULL)
			write(fd, " ", 1);
		index++;
	}
}

void	ft_builtin_echo(t_cluster *cluster, t_state *state)
{
	char	**cmd;
	int		fd;
	int		no_newline;
	int		index;

	cmd = cluster->cmd;
	fd = cluster->files->fd_output;
	index = ft_parse_echo_flags(cmd, &no_newline);
	if (cmd[1] == NULL)
	{
		if (!no_newline)
			write(fd, "\n", 1);
		state->error = 0;
		return ;
	}
	ft_print_echo_args(cmd, index, fd);
	if (!no_newline)
		write(fd, "\n", 1);
	state->error = 0;
}
