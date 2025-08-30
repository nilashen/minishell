#include "../includes/minishell.h"

static void	ft_open_pipes(t_state *state)
{
	int	**fd;
	int	i;

	i = -1;
	fd = (int **) malloc(sizeof(int *) * state->cmd_count);
	fd[state->cmd_count - 1] = NULL;
	while (++i < state->cmd_count - 1)
		fd[i] = malloc(sizeof(int) * 2);
	state->fd = fd;
	i = -1 ;
	while (++i < state->cmd_count - 1)
		pipe(state->fd[i]);
}

static char	*ft_cmd_get(t_state *state, t_cluster *cluster)
{
	ft_find_and_exec_command(state, cluster);
	return (NULL);
}

static void	ft_execve(t_state *state, t_cluster *cluster, int i, int check)
{
	char	*cmd_path;

	ft_dup_init(state, cluster, i, check);
	if (state->cmd_count > 1 && check > 0)
	{
		ft_route(state, cluster);
		free(state->line);
		exit(0);
	}
	cmd_path = ft_cmd_get(state, cluster);
	ft_reset_signals_child();
	if (cmd_path == NULL && cluster->cmd[0] != NULL)
	{
		ft_executer_error(cluster->cmd, "command not found", 127);
	}
	exit(0);
}

static void	ft_process_cluster(t_state *state, t_cluster *tmp, int *i, int *check)
{
	*check = ft_check_built(tmp);
	if (tmp->cmd)
	{
		if (*check > 0 && state->cmd_count == 1)
			ft_route(state, tmp);
		else
		{
			g_sig_status = 1;
			tmp->pid = fork();
			if (tmp->pid == 0)
			{
				ft_reset_signals_child();
				ft_execve(state, tmp, *i, *check);
			}
		}
		(*i)++;
	}
}

void	ft_executer(t_state *state, int i)
{
	t_cluster	*tmp;
	int			check;

	ft_open_pipes(state);
	tmp = state->cluster;
	while (tmp)
	{
		ft_process_cluster(state, tmp, &i, &check);
		tmp = tmp->next;
	}
	ft_close_pipe(state, check);
}
