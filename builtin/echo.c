#include "../includes/minishell.h"

static int	ft_flag_check(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][j] != '-')
			return (i);
		if (cmd[i][j] == '-' && cmd[i][j + 1] == '\0')
			return (i);
		while (cmd[i][++j])
		{
			if (cmd[i][j] != 'n')
				return (i);
		}
		i++;
	}
	return (i);
}

static int	ft_should_print_newline(int index)
{
	if (index == 1)
		return (1);
	return (0);
}

static void	ft_print_args(char **cmd, int fd, int start_index)
{
	int	i;

	i = start_index;
	while (cmd[i])
	{
		write(fd, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
}

static void	ft_handle_empty_args(int fd, int print_newline, t_state *state)
{
	if (print_newline)
		write(fd, "\n", 1);
	state->error = 0;
}

void	ft_echo(t_cluster *cluster, t_state *state)
{
	int	fd;
	int	index;
	int	print_newline;

	fd = cluster->files->fd_output;
	index = ft_flag_check(cluster->cmd);
	print_newline = ft_should_print_newline(index);
	if (cluster->cmd[1] == NULL)
	{
		ft_handle_empty_args(fd, print_newline, state);
		return ;
	}
	ft_print_args(cluster->cmd, fd, index);
	if (print_newline)
		write(fd, "\n", 1);
	state->error = 0;
}
