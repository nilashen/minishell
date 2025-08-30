#include "../includes/minishell.h"

void	ft_int_free(t_state *state)
{
	int	i;

	i = 0;
	if (state->fd)
	{
		while (state->fd[i])
		{
			free(state->fd[i]);
			i++;
		}
		free(state->fd);
	}
	state->fd = NULL;
}

void	ft_wait(t_state *state, int check)
{
	t_cluster	*tmp;
	int			result;

	tmp = state->cluster;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			waitpid(tmp->pid, &result, 0);
			if (!(check > 0))
				state->error = result >> 8;
		}
		tmp = tmp->next;
	}
	ft_int_free(state);
}

void	ft_close_pipe(t_state *state, int check)
{
	int	i;

	i = 0;
	while (i < state->cmd_count -1)
	{
		if (state->fd[i][0])
			close(state->fd[i][0]);
		if (state->fd[i][1])
			close(state->fd[i][1]);
		i++;
	}
	ft_wait(state, check);
}

void	ft_pipe_connect(t_state *state, t_cluster *cluster, int i, int check)
{
	int	j;

	(void)check;
	if (state->cluster == cluster)  // First command
		dup2(state->fd[i][1], STDOUT_FILENO);
	else if (cluster->next == NULL)  // Last command
		dup2(state->fd[i - 1][0], STDIN_FILENO);
	else  // Middle command
	{
		dup2(state->fd[i - 1][0], STDIN_FILENO);
		dup2(state->fd[i][1], STDOUT_FILENO);
	}
	j = 0;
	while (j < state->cmd_count - 1)  // Close ALL pipe fds in child
	{
		close(state->fd[j][0]);
		close(state->fd[j][1]);
		j++;
	}
}

void	ft_dup_init(t_state *state, t_cluster *cluster, int i, int check)
{
	int		fd[2];
	t_files	*files;

	files = cluster->files;
	if (state->cmd_count > 1)
		ft_pipe_connect(state, cluster, i, check);
	if (files->fd_input == -2)
	{
		pipe(fd);
		write(fd[1], files->heredoc, ft_strlen(files->heredoc));
		close (fd[1]);
		if (cluster->next || ft_strcmp(cluster->cmd[0], "echo"))
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (files->fd_output >= 2)
		dup2(files->fd_output, STDOUT_FILENO);
	if (files->fd_input >= 2)
		dup2(files->fd_input, STDIN_FILENO);
}
