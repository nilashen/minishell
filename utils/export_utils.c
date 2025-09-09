/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:04:13 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:04:14 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_validate_key(char *arg, t_state *state)
{
	int	i;

	if (!arg || arg[0] == '\0')
	{
		ft_key_error(arg, "export", state);
		return (0);
	}
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_key_error(arg, "export", state);
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_key_error(arg, "export", state);
			return (0);
		}
		i++;
	}
	return (i);
}

void	ft_update_pwd_env(t_state **state, char *old_pwd)
{
	char	*oldpwd_entry;

	oldpwd_entry = ft_strjoin("OLDPWD=", old_pwd);
	if (oldpwd_entry)
	{
		ft_add_exp(state, oldpwd_entry);
		ft_add_env(state, oldpwd_entry);
		free(oldpwd_entry);
		(*state)->error = 0;
	}
	else
		(*state)->error = 1;
}
