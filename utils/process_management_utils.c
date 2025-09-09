/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:31:07 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 17:57:28 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_wait_status(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (130);
		}
		else if (sig == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			return (131);
		}
		else if (sig == SIGPIPE)
			return (0);
		else
			return (128 + sig);
	}
	else if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	return (0);
}

void	ft_wait_single_command(t_state *state)
{
	t_cluster	*tmp;
	int			status;

	tmp = state->cluster;
	g_sig_status = IN_PARENT;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			waitpid(tmp->pid, &status, 0);
			state->error = ft_handle_wait_status(status);
		}
		tmp = tmp->next;
	}
	g_sig_status = 0;
}

void	ft_setup_input_redirection(t_files *files)
{
	int	fd[2];

	if (files->fd_input == -2)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		write(fd[1], files->heredoc, ft_strlen(files->heredoc));
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else if (files->fd_input >= 2)
	{
		dup2(files->fd_input, STDIN_FILENO);
		close(files->fd_input);
	}
}

void	ft_setup_output_redirection(t_files *files)
{
	if (files->fd_output >= 2)
	{
		dup2(files->fd_output, STDOUT_FILENO);
		close(files->fd_output);
	}
}
