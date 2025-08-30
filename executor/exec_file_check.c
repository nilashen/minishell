#include "../includes/minishell.h"

static int	ft_check_file_permissions(t_cluster *cluster, struct stat *file_info, char **envp)
{
	if (file_info->st_mode & S_IXUSR)
	{
		execve(cluster->cmd[0], cluster->cmd, envp);
		ft_executer_error(cluster->cmd, "execve failed", 127);
	}
	else
		ft_executer_error(cluster->cmd, "Permission denied", 126);
	return (1);
}

static int	ft_handle_directory_error(t_state *state, t_cluster *cluster)
{
	if (ft_strcmp(state->cluster->cmd[0], ".") == 0)
		ft_executer_error(cluster->cmd, "filename argument required", 2);
	else if (ft_strcmp(state->cluster->cmd[0], "..") == 0)
		ft_executer_error(cluster->cmd, "command not found", 127);
	else
		ft_executer_error(cluster->cmd, "Is a directory", 126);
	return (1);
}

static int	ft_handle_stat_success(t_state *state, t_cluster *cluster, struct stat *file_info)
{
	if (S_ISREG(file_info->st_mode))
		return (ft_check_file_permissions(cluster, file_info, state->envp));
	else
		return (ft_handle_directory_error(state, cluster));
}

int	ft_check_executable_file(t_state *state, t_cluster *cluster)
{
	struct stat	file_info;

	if (stat(cluster->cmd[0], &file_info) == 0)
		return (ft_handle_stat_success(state, cluster, &file_info));
	else
	{
		ft_executer_error(cluster->cmd, "No such file or directory", 127);
		return (1);
	}
}