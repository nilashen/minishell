/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:39:45 by nashena           #+#    #+#             */
/*   Updated: 2025/08/05 16:20:14 by nashena          ###   ########.fr       */
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

static int	handle_output_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_heredoc(t_redir *redir)
{
	int		pipe_fds[2];
	char	*line;
	size_t	delimiter_len;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	delimiter_len = ft_strlen(redir->file);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, redir->file, delimiter_len) == 0
			&& line[delimiter_len] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fds[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fds[1]);
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fds[0]);
		return (-1);
	}
	close(pipe_fds[0]);
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
		else if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND)
		{
			if (handle_output_redir(current) == -1)
				return (-1);
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			if (handle_heredoc(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
