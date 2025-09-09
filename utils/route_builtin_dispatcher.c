/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_builtin_dispatcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:34:39 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:34:44 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_dispatch_builtin(t_state *state, t_cluster *tmp)
{
	if ((tmp->cmd) == NULL)
		return ;
	else if (ft_strcmp(tmp->cmd[0], "cd") == 0)
		ft_builtin_cd(&state);
	else if (ft_strcmp(tmp->cmd[0], "pwd") == 0)
		ft_builtin_pwd(tmp, state);
	else if (ft_strcmp(tmp->cmd[0], "echo") == 0)
		ft_builtin_echo(tmp, state);
	else if (ft_strcmp(tmp->cmd[0], "export") == 0)
		ft_export_status(&state, tmp);
	else if ((ft_strcmp(tmp->cmd[0], "env") == 0
			|| ft_strcmp(tmp->cmd[0], "ENV") == 0))
		ft_print_env(state, tmp);
	else if (ft_strcmp(tmp->cmd[0], "unset") == 0)
		ft_unset_variable(&state, tmp);
}

int	ft_is_builtin_command(t_cluster *cluster)
{
	if ((cluster->cmd) == NULL)
		return (-1);
	else if (ft_strcmp(cluster->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cluster->cmd[0], "pwd") == 0)
		return (2);
	else if (ft_strcmp(cluster->cmd[0], "echo") == 0)
		return (3);
	else if (ft_strcmp(cluster->cmd[0], "export") == 0)
		return (4);
	else if (ft_strcmp(cluster->cmd[0], "env") == 0
		|| ft_strcmp(cluster->cmd[0], "ENV") == 0)
		return (5);
	else if (ft_strcmp(cluster->cmd[0], "unset") == 0)
		return (6);
	else if (ft_strcmp(cluster->cmd[0], "exit") == 0)
		return (7);
	return (-1);
}
