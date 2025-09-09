/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:07:18 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:07:26 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cleanup_arrays(t_parser *pars, int last_index)
{
	int	i;

	i = -1;
	while (++i < last_index)
	{
		if (pars->src && pars->src[i])
			free(pars->src[i]);
		if (pars->cleaned && pars->cleaned[i])
			free(pars->cleaned[i]);
	}
	if (pars->src)
		free(pars->src);
	if (pars->cleaned)
		free(pars->cleaned);
}

int	ft_init_arrays(t_parser *pars, int len)
{
	pars->src = malloc(sizeof(char *) * (len + 1));
	pars->cleaned = malloc(sizeof(char *) * (len + 1));
	if (!pars->src || !pars->cleaned)
	{
		ft_cleanup_arrays(pars, 0);
		return (0);
	}
	return (1);
}

int	ft_try_path_command(t_state *state, t_cluster *cluster, int i)
{
	char	*tmp;
	char	*command;

	tmp = ft_strjoin(state->sep_path[i], "/");
	if (!tmp)
		exit(1);
	command = ft_strjoin(tmp, cluster->cmd[0]);
	free(tmp);
	if (!command)
		exit(1);
	if (access(command, X_OK) == 0)
	{
		execve(command, cluster->cmd, state->envp);
		ft_pipeline_error(cluster->cmd, " Permission denied", 126);
	}
	free(command);
	return (0);
}
