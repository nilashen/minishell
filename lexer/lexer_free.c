#include "../includes/minishell.h"

static void	ft_close_cluster_files_fds(t_files *files)
{
	if (!files)
		return ;
	if (files->fd_input > 2)
		close(files->fd_input);
	if (files->fd_output > 2)
		close(files->fd_output);
}

static void	ft_free_cluster_files_strings(t_files *files)
{
	if (!files)
		return ;
	if (files->input)
		free(files->input);
	if (files->output)
		free(files->output);
	if (files->heredoc)
		free(files->heredoc);
}

static void	ft_free_single_cluster(t_cluster *cluster)
{
	if (!cluster)
		return ;
	if (cluster->cmd)
		ft_free_double_str(cluster->cmd);
	if (cluster->files)
	{
		ft_close_cluster_files_fds(cluster->files);
		ft_free_cluster_files_strings(cluster->files);
		free(cluster->files);
	}
	free(cluster);
}

static t_cluster	*ft_get_next_cluster(t_cluster *current)
{
	if (!current)
		return (NULL);
	return (current->next);
}

void	ft_all_cluster_free(t_state *state)
{
	t_cluster	*current;
	t_cluster	*next;

	if (!state || !state->cluster)
		return ;
	current = state->cluster;
	while (current)
	{
		next = ft_get_next_cluster(current);
		ft_free_single_cluster(current);
		current = next;
	}
	state->cluster = NULL;
}
