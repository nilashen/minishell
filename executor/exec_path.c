#include "../includes/minishell.h"

static char	*ft_build_command_path(char *path_dir, char *cmd)
{
	char	*tmp;
	char	*command;

	tmp = ft_strjoin(path_dir, "/");
	if (!tmp)
		return (NULL);
	command = ft_strjoin(tmp, cmd);
	free(tmp);
	return (command);
}

static int	ft_execute_if_found(char *command, char **cmd, char **envp)
{
	if (access(command, X_OK) == 0)
	{
		execve(command, cmd, envp);
		return (1);
	}
	return (0);
}

static void	ft_search_in_path(t_state *state, t_cluster *cluster)
{
	char	*command;
	int		i;

	i = 0;
	while (state->sep_path[i])
	{
		command = ft_build_command_path(state->sep_path[i], cluster->cmd[0]);
		if (!command)
		{
			ft_executer_error(cluster->cmd, "malloc error", 1);
			return;
		}
		if (ft_execute_if_found(command, cluster->cmd, state->envp))
		{
			free(command);
			ft_executer_error(cluster->cmd, "execve failed", 127);
			return;
		}
		free(command);
		i++;
	}
	ft_executer_error(cluster->cmd, "command not found", 127);
}

static int	ft_handle_absolute_path(t_state *state, t_cluster *cluster)
{
	if (cluster->cmd[0][0] == '/' || cluster->cmd[0][0] == '.')
		return (ft_check_executable_file(state, cluster));
	return (0);
}

void	ft_find_and_exec_command(t_state *state, t_cluster *cluster)
{
	if (cluster->cmd[0] == NULL)
		return;
	if (ft_handle_absolute_path(state, cluster))
		return;
	if (!state->sep_path)
	{
		ft_executer_error(cluster->cmd, "command not found", 127);
		return;
	}
	ft_search_in_path(state, cluster);
}