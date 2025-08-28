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

void	ft_echo(t_cluster *cluster, t_state *state)
{
	char	**cmd;
	int		i;
	int		fd;
	int		index;

	fd = cluster->files->fd_output;
	index = ft_flag_check(cluster->cmd);
	i = index;
	cmd = cluster->cmd;
	if (cmd[1] == NULL)
	{
		write(fd, "\n", 2);
		return ;
	}
	while (cmd[index])
	{
		write(fd, cmd[index], ft_strlen(cmd[index]));
		if (cmd[index + 1] != NULL)
			write(fd, " ", 1);
		index++;
	}
	if (i == 1)
		write(fd, "\n", 1);
	state->error = 0;
}
