/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:20:01 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 15:59:27 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_args(char **cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (0);
	while (cmd[count])
		count++;
	return (count);
}

void	ft_cd_error(char *dir, t_state *state)
{
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, dir, ft_strlen(dir));
	if (errno == ENOTDIR)
		write(STDERR_FILENO, ": Not a directory\n", 18);
	else if (errno == ENOENT)
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	else if (errno == EACCES)
		write(STDERR_FILENO, ": Permission denied\n", 20);
	else
	{
		write(STDERR_FILENO, ": ", 2);
		perror("");
	}
	state->error = 1;
}
