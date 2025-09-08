#include "../includes/minishell.h"

static void	ft_close_cluster_fds(t_files *files)
{
	if (files->fd_input > 2)
		close(files->fd_input);
	if (files->fd_output > 2)
		close(files->fd_output);
}

static void	ft_free_file_strings(t_files *files)
{
	if (files->input)
	{
		free(files->input);
		files->input = NULL;
	}
	if (files->output)
	{
		free(files->output);
		files->output = NULL;
	}
	if (files->heredoc)
	{
		free(files->heredoc);
		files->heredoc = NULL;
	}
}

static void	ft_free_single_cluster(t_cluster *cluster)
{
	if (!cluster)
		return ;
	
	ft_free_double_str(cluster->cmd);
	
	if (cluster->files)
	{
		ft_close_cluster_fds(cluster->files);
		ft_free_file_strings(cluster->files);
		free(cluster->files);
	}
	
	free(cluster);
}

void	ft_all_cluster_free(t_state *state)
{
	t_cluster	*tmp;
	t_cluster	*next;

	if (!state || !state->cluster)
		return ;
	
	tmp = state->cluster;
	while (tmp)
	{
		next = tmp->next;
		ft_free_single_cluster(tmp);
		tmp = next;
	}
	
	state->cluster = NULL;
}
