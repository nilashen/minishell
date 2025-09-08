#include "../includes/minishell.h"

static void	ft_exec_file_check(t_state *state, t_cluster *cluster)
{
	struct stat	file_info;

	if (stat(cluster->cmd[0], &file_info) == 0)
	{
		if (S_ISREG(file_info.st_mode))
		{
			if (file_info.st_mode & S_IXUSR)
			{
				execve(cluster->cmd[0], cluster->cmd, state->envp);
				exit(0);
			}
			else
				ft_execute_pipeline_error(cluster->cmd, "permission denied", 126);
		}
		else
		{
			if (ft_strcmp(state->cluster->cmd[0], ".") == 0)
				ft_execute_pipeline_error(cluster->cmd, "filename argument required",
					2);
			else if (ft_strcmp(state->cluster->cmd[0], "..") == 0)
				ft_execute_pipeline_error(cluster->cmd, "commond not found", 127);
			else
				ft_execute_pipeline_error(cluster->cmd, "is a directory", 126);
		}
	}
}

static char	*ft_cmd_get(t_state *state, t_cluster *cluster)
{
	int	i;

	i = 0;
	if (cluster->cmd[0] == NULL)
		return (NULL);
	if (cluster->cmd[0][0] == '/' || cluster->cmd[0][0] == '.')
		ft_exec_file_check(state, cluster);
	while (state->sep_path && state->sep_path[i])
	{
		ft_try_path_command(state, cluster, i);
		i++;
	}
	return (NULL);
}

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

static void	ft_execve(t_state *state, t_cluster *cluster, int i, int check)
{
    char	*cmd_path;

    // Reset signal handling for child processes
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    
    ft_dup_init(state, cluster, i, check);
    if (state->cmd_count > 1 && check > 0)
    {
        ft_dispatch_builtin(state, cluster);
        free(state->line);
        exit(state->error);
    }
    cmd_path = ft_cmd_get(state, cluster);
    if (cmd_path == NULL && cluster->cmd[0] != NULL)
        ft_execute_pipeline_error(cluster->cmd, "command not found", 127);
    exit(127);
}

void	ft_execute_pipeline(t_state *state, int i)
{
	t_cluster	*tmp;
	int			check;

	ft_open_pipes(state);
	tmp = state->cluster;
	while (tmp)
	{
		check = ft_is_builtin_command(tmp);
		if (tmp->cmd)
		{
			if (check > 0 && state->cmd_count == 1)
				ft_dispatch_builtin(state, tmp);
			else
			{
				g_sig_status = IN_CAT;
				tmp->pid = fork();
				if (tmp->pid == 0)
					ft_execve(state, tmp, i, check);
			}
			i++;
		}
		tmp = tmp->next;
	}
	ft_close_pipe(state, check);
}
