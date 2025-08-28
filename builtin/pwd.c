#include "../includes/minishell.h"

void	ft_pwd(t_cluster *cluster, t_state *state)
{
	char	pwd[1024];
	int		fd;

	fd = cluster->files->fd_output;
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
		state->error = 0;
	}
	else
		perror("PWD");
}