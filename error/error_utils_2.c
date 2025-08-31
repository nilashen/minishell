#include "../includes/minishell.h"

static void	ft_free_cluster_cmd(t_cluster *cluster)
{
	int	i;

	if (!cluster || !cluster->cmd)
		return ;
	i = 0;
	while (cluster->cmd[i])
	{
		free(cluster->cmd[i]);
		cluster->cmd[i] = NULL;
		i++;
	}
	free(cluster->cmd);
	cluster->cmd = NULL;
}

static void	ft_close_cluster_fds(t_cluster *cluster)
{
	if (!cluster || !cluster->files)
		return ;
	if (cluster->files->fd_input > 2)
		close(cluster->files->fd_input);
	if (cluster->files->fd_output > 2)
		close(cluster->files->fd_output);
}

static void	ft_free_cluster_files_strings(t_cluster *cluster)
{
	if (!cluster || !cluster->files)
		return ;
	if (cluster->files->heredoc)
	{
		free(cluster->files->heredoc);
		cluster->files->heredoc = NULL;
	}
	if (cluster->files->input)
	{
		free(cluster->files->input);
		cluster->files->input = NULL;
	}
	if (cluster->files->output)
	{
		free(cluster->files->output);
		cluster->files->output = NULL;
	}
}

void	ft_cluster_free(t_cluster *cluster)
{
	if (!cluster)
		return ;
	ft_free_cluster_cmd(cluster);
	ft_close_cluster_fds(cluster);
	ft_free_cluster_files_strings(cluster);
	if (cluster->files)
	{
		free(cluster->files);
		cluster->files = NULL;
	}
	free(cluster);
}

t_cluster	*ft_file_open_error(t_cluster *cluster, char *file)
{
	if (file)
		perror(file);
	ft_cluster_free(cluster);
	return (NULL);
}
