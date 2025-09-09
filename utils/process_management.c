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
    int			status;
    int			last_exit_code;

    (void)check;
    last_exit_code = 0;
    tmp = state->cluster;
    
    g_sig_status = IN_PARENT;
    
    while (tmp)
    {
        if (tmp->pid > 0)
        {
            if (waitpid(tmp->pid, &status, 0) > 0)
            {
                if (WIFSIGNALED(status))
                {
                    int sig = WTERMSIG(status);
                    if (sig == SIGINT)
                    {
                        last_exit_code = 130;
                        write(STDOUT_FILENO, "\n", 1); // Add newline after ^C
                    }
                    else if (sig == SIGQUIT)
                    {
                        last_exit_code = 131;
                        write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
                    }
                    else if (sig == SIGPIPE)
                        last_exit_code = 0;
                    else
                        last_exit_code = 128 + sig;
                }
                else if (WIFEXITED(status))
                {
                    last_exit_code = WEXITSTATUS(status);
                }
            }
        }
        tmp = tmp->next;
    }
    
    g_sig_status = 0;
    state->error = last_exit_code;
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
	if (state->cluster == cluster)
		dup2(state->fd[i][1], STDOUT_FILENO);
	else if (cluster->next == NULL)
		dup2(state->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(state->fd[i - 1][0], STDIN_FILENO);
		dup2(state->fd[i][1], STDOUT_FILENO);
	}
	ft_close_pipe(state, check);
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
