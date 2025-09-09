/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:41:15 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 17:05:24 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc_helper(char *line, t_files *node)
{
	if (line == NULL)
	{
		close(node->fd_heredoc[1]);
		exit(0);
	}
	if (ft_strcmp(line, node->input) == 0)
	{
		free(line);
		close(node->fd_heredoc[1]);
		exit(0);
	}
	write(node->fd_heredoc[1], line, ft_strlen(line));
	write(node->fd_heredoc[1], "\n", 1);
	free(line);
}

int	ft_parent_heredoc(t_files *node, int pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	close(node->fd_heredoc[1]);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			return (130);
		else if (sig == SIGQUIT)
			return (131);
		else
			return (128 + sig);
	}
	else if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	ft_heredoc(t_files *node)
{
	int	pid;

	if (pipe(node->fd_heredoc) == -1)
		return (perror("pipe"), 3);
	pid = fork();
	if (pid == 0)
		ft_heredoc_child(node);
	else if (pid > 0)
		return (ft_heredoc_parent(node, pid));
	perror("fork");
	close(node->fd_heredoc[0]);
	close(node->fd_heredoc[1]);
	return (3);
}

char	*ft_read_all_heredoc(int fd)
{
	char	*result;
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (line != NULL)
	{
		temp = result;
		result = ft_strjoin(temp, line);
		free(temp);
		free(line);
		if (!result)
			return (NULL);
		line = get_next_line(fd);
	}
	return (result);
}

void	ft_heredoc_check(t_files *node, char **arg)
{
	int	i;

	i = 0;
	node->heredoc = ft_strdup("");
	while (arg[i])
	{
		if (ft_strcmp(arg[i], "<<") == 0)
		{
			free(node->input);
			node->input = ft_strdup(arg[i + 1]);
			node->error = ft_heredoc(node);
			if (node->error == 130 || node->error == 3)
				return (ft_handle_heredoc_error(node));
			if (node->error == 0)
				ft_handle_heredoc_success(node);
			i++;
		}
		i++;
	}
	if (!node->heredoc)
		node->heredoc = ft_strdup("");
}
