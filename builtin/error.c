/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:09:34 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 11:09:35 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_notdefine_dir(char *s, t_state *state)
{
	state->error = 1;
	write(2, "cd: ", 4);
	write(2, s, ft_strlen(s));
	write(2, " ", 1);
	write(2, "not set\n", ft_strlen("not set\n"));
}

void	ft_builtin_cd_error(char *dir, t_state *state)
{
	state->error = 1;
	write(2, "cd: ", ft_strlen("cd: "));
	perror(dir);
}

void	ft_key_error(char *s, char *cmd, t_state *state)
{
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		write (2, "export: ", ft_strlen("export: "));
	else
		write (2, "unset: ", ft_strlen("unset: "));
	write (2, s, ft_strlen(s));
	write (2, ": not a valid identifier\n",
		ft_strlen(": not a valid identifier\n"));
	state->error = 1;
}
