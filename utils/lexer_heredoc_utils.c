/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:57:26 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:57:39 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc_child(t_files *node)
{
	char	*line;

	close(node->fd_heredoc[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		ft_heredoc_helper(line, node);
	}
	exit(1);
}

int	ft_heredoc_parent(t_files *node, int pid)
{
	int	status;

	close(node->fd_heredoc[1]);
	status = ft_parent_heredoc(node, pid);
	if (status != 0)
		close(node->fd_heredoc[0]);
	return (status);
}

void	ft_handle_heredoc_error(t_files *node)
{
	if (node->error == 130)
	{
		free(node->heredoc);
		node->heredoc = ft_strdup("");
	}
}

void	ft_handle_heredoc_success(t_files *node)
{
	free(node->heredoc);
	node->heredoc = ft_read_all_heredoc(node->fd_heredoc[0]);
	if (!node->heredoc)
		node->heredoc = ft_strdup("");
	close(node->fd_heredoc[0]);
}
