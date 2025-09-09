/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:27:57 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 18:00:22 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_int_free(t_state *state)
{
	int	i;

	i = 0;
	if (state->fd)
	{
		while (i < state->cmd_count - 1)
		{
			if (state->fd[i])
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
				last_exit_code = ft_handle_wait_status(status);
		}
		tmp = tmp->next;
	}
	g_sig_status = 0;
	state->error = last_exit_code;
}

void	ft_close_pipe(t_state *state, int check)
{
	int	i;

	i = 0;
	while (i < state->cmd_count - 1)
	{
		if (state->fd[i])
		{
			close(state->fd[i][0]);
			close(state->fd[i][1]);
		}
		i++;
	}
	ft_wait(state, check);
	ft_int_free(state);
}

void	ft_pipe_connect(t_state *state, t_cluster *cluster, int i, int check)
{
	int	j;

	(void)check;
	if (state->cluster == cluster)
		dup2(state->fd[i][1], STDOUT_FILENO);
	else if (cluster->next == NULL)
		dup2(state->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(state->fd[i - 1][0], STDIN_FILENO);
		dup2(state->fd[i][1], STDOUT_FILENO);
	}
	j = 0;
	while (j < state->cmd_count - 1)
	{
		close(state->fd[j][0]);
		close(state->fd[j][1]);
		j++;
	}
}

void	ft_dup_init(t_state *state, t_cluster *cluster, int i, int check)
{
	t_files	*files;

	files = cluster->files;
	if (state->cmd_count > 1)
		ft_pipe_connect(state, cluster, i, check);
	ft_setup_input_redirection(files);
	ft_setup_output_redirection(files);
}
