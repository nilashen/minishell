#include "../includes/minishell.h"

static void	ft_open_pipes(t_state *state)
{
	int	**fd;
	int	i;

	i = -1;
	fd = (int **) malloc(sizeof(int *) * state->cmd_count);
	if (!fd)
		return ;
	fd[state->cmd_count - 1] = NULL;
	while (++i < state->cmd_count - 1)
		fd[i] = malloc(sizeof(int) * 2);
	state->fd = fd;
	i = -1 ;
	while (++i < state->cmd_count - 1)
		pipe(state->fd[i]);
}

static void	ft_execve_builtin(t_state *state, t_cluster *cluster, int check)
{
	ft_dup_init(state, cluster, 0, check);
	ft_route(state, cluster);
	exit(state->error);
}

static void	ft_execve_external(t_state *state, t_cluster *cluster, int i)
{
	ft_dup_init(state, cluster, i, 0);
	ft_find_and_exec_command(state, cluster);
	exit(127);
}

static void	ft_process_cluster(t_state *state, t_cluster *tmp, int *i, int *check)
{
	*check = ft_check_built(tmp);
	if (tmp->cmd && tmp->cmd[0])
	{
		if (*check > 0 && state->cmd_count == 1)
		{
			ft_route(state, tmp);
		}
		else
		{
			g_sig_status = 1;
			tmp->pid = fork();
			if (tmp->pid == 0)
			{
				ft_reset_signals_child();
				if (*check > 0)
					ft_execve_builtin(state, tmp, *check);
				else
					ft_execve_external(state, tmp, *i);
			}
		}
		(*i)++;
	}
}

void	ft_executer(t_state *state, int i)
{
	t_cluster	*tmp;
	int			check;

	if (state->cmd_count > 1)
		ft_open_pipes(state);
	tmp = state->cluster;
	while (tmp)
	{
		ft_process_cluster(state, tmp, &i, &check);
		tmp = tmp->next;
	}
	if (state->cmd_count > 1)
		ft_close_pipe(state, check);
	else if (check <= 0)
		ft_wait(state, check);
}
