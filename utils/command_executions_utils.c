/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:59:34 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 17:59:23 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_builtin(t_state *state, t_cluster *tmp, int check, int *i)
{
	if (check == 7)
	{
		ft_builtin_exit(state, tmp);
		(*i)++;
		return ;
	}
	if (check > 0 && state->cmd_count == 1)
		ft_dispatch_builtin(state, tmp);
	else
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
			ft_execve(state, tmp, *i, check);
		else if (tmp->pid < 0)
		{
			perror("fork");
			state->error = 1;
		}
	}
	(*i)++;
}

int	**ft_allocate_pipes(t_state *state)
{
	int	**fd;
	int	i;

	if (state->cmd_count <= 1)
		return (NULL);
	fd = (int **)malloc(sizeof(int *) * state->cmd_count);
	if (!fd)
		return (NULL);
	i = 0;
	while (i < state->cmd_count - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			while (--i >= 0)
				free(fd[i]);
			free(fd);
			return (NULL);
		}
		i++;
	}
	fd[state->cmd_count - 1] = NULL;
	return (fd);
}

int	ft_create_pipes(int **fd, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe");
			while (i-- >= 0)
			{
				close(fd[i][0]);
				close(fd[i][1]);
				free(fd[i]);
			}
			free(fd);
			return (-1);
		}
		i++;
	}
	return (0);
}
