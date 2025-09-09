/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:39:58 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 14:41:47 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	validate_and_exit(t_state *state, char *arg)
{
	int	i;
	int	exit_code;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i++]))
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			ft_full_free(state, 2);
		}
	}
	exit_code = ft_atoi(arg) % 256;
	if (exit_code < 0)
		exit_code = 256 + exit_code;
	ft_full_free(state, exit_code);
}

int	ft_builtin_exit(t_state *state, t_cluster *cluster)
{
	if (cluster->cmd[1] && cluster->cmd[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		state->error = 1;
		return (1);
	}
	if (cluster->cmd[1])
		validate_and_exit(state, cluster->cmd[1]);
	ft_full_free(state, state->error);
	return (0);
}
