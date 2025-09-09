/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:36:43 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:36:44 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_redirect(char *arg)
{
	if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0
		|| ft_strcmp(arg, "<<") == 0 || ft_strcmp(arg, ">>") == 0)
		return (1);
	else
		return (0);
}

char	**ft_find_cmd(char **arg, int len)
{
	int		i;
	char	**cmd;
	int		j;

	i = -1;
	j = 0;
	cmd = malloc(sizeof(char *) * (len + 1));
	while (arg[++i])
	{
		if (i == 0)
		{
			if (ft_check_redirect(arg[i]) == 1)
				i++;
			else
				cmd[j++] = ft_strdup(arg[i]);
		}
		else
		{
			if (ft_check_redirect(arg[i]) == 1)
				i++;
			else if (ft_check_redirect(arg[i -1]) == 0)
				cmd[j++] = ft_strdup(arg[i]);
		}
	}
	return (cmd);
}

int	ft_cmd_len(char **arg)
{
	int	i;
	int	len;
	int	rdr;

	i = 0;
	rdr = 0;
	len = 0;
	while (arg[i++])
		len++;
	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0
			|| ft_strcmp(arg[i], ">>") == 0 || ft_strcmp(arg[i], "<<") == 0)
			rdr++;
		i++;
	}
	return (len - (rdr * 2));
}

char	**ft_fill_cmd(char **arg)
{
	int		len;
	char	**cmd;

	len = ft_cmd_len(arg);
	cmd = ft_find_cmd(arg, len);
	cmd[len] = NULL;
	return (cmd);
}
