/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:06:22 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 11:06:48 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_parse_echo_flags(char **cmd, int *no_newline)
{
	int	index;
	int	j;

	index = 1;
	*no_newline = 0;
	while (cmd[index] && cmd[index][0] == '-' && cmd[index][1] == 'n')
	{
		j = 1;
		while (cmd[index][j] == 'n')
			j++;
		if (cmd[index][j] == '\0')
		{
			*no_newline = 1;
			index++;
		}
		else
			break ;
	}
	return (index);
}

static void	ft_print_echo_args(char **cmd, int index, int fd)
{
	while (cmd[index])
	{
		write(fd, cmd[index], ft_strlen(cmd[index]));
		if (cmd[index + 1] != NULL)
			write(fd, " ", 1);
		index++;
	}
}

void	ft_builtin_echo(t_cluster *cluster, t_state *state)
{
	char	**cmd;
	int		fd;
	int		no_newline;
	int		index;

	cmd = cluster->cmd;
	fd = cluster->files->fd_output;
	index = ft_parse_echo_flags(cmd, &no_newline);
	if (cmd[1] == NULL)
	{
		if (!no_newline)
			write(fd, "\n", 1);
		state->error = 0;
		return ;
	}
	ft_print_echo_args(cmd, index, fd);
	if (!no_newline)
		write(fd, "\n", 1);
	state->error = 0;
}
