/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:45:00 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 14:45:33 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_validate_unset_key(char *key, t_state *state)
{
	int	i;

	if (!key || key[0] == '\0')
	{
		ft_key_error(key, "unset", state);
		return (0);
	}
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		ft_key_error(key, "unset", state);
		return (0);
	}
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			ft_key_error(key, "unset", state);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_unset_variable(t_state **state, t_cluster *cluster)
{
	int		i;
	int		has_error;

	i = 1;
	has_error = 0;
	if (!cluster->cmd[i])
	{
		(*state)->error = 0;
		return ;
	}
	while (cluster->cmd[i])
	{
		if (!ft_validate_unset_key(cluster->cmd[i], *state))
		{
			has_error = 1;
			i++;
			continue ;
		}
		ft_del_node(&(*state)->env, cluster->cmd[i]);
		ft_del_node(&(*state)->exp, cluster->cmd[i]);
		i++;
	}
	(*state)->error = has_error;
}
