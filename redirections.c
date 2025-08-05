/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:39:45 by nashena           #+#    #+#             */
/*   Updated: 2025/08/05 10:44:22 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redir(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}


int	setup_redirections(t_cmd *cmd)
{
	t_redir	*current;

	if (!cmd)
		return (0);
	current = cmd->redirs;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
		{
			if (handle_input_redir(current) == -1)
				return (-1);
		}
	current = current->next;
	}
	return (0);
}
