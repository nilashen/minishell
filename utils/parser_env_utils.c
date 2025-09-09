/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:18:29 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:20:47 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pars_str(char *s, t_parser *prs)
{
	if (prs->dollar_is_first)
	{
		prs->len_dollar[0] = prs->d +1;
		while (s[prs->d] != '\0' && s[prs->d] != ' ')
			prs->d++;
		prs->len_dollar[1] = prs->d -1;
		if (s[prs->d] != ' ' && prs->d >= (int)(ft_strlen(s) - 1))
		{
			prs->len_str[0] = -1;
			return ;
		}
		prs->len_str[0] = prs->d;
		while ((s[prs->d] && s[prs->d] != '$'))
			prs->d++;
		if (s[prs->d] == '$' && !ft_dol(s, prs->d, prs))
		{
			prs->d++;
			while ((s[prs->d] && s[prs->d] == '$' && !ft_dol(s, prs->d, prs))
				|| (s[prs->d] && s[prs->d] != '$'))
				prs->d++;
		}
		prs->len_str[1] = prs->d -1;
	}
	else
		ft_pars_str_helper(s, prs);
}

void	ft_pars_str_helper(char *s, t_parser *prs)
{
	prs->len_str[0] = prs->d;
	while ((s[prs->d] && s[prs->d] != '$'))
		prs->d++;
	if (s[prs->d] == '$' && !ft_dol(s, prs->d, prs))
	{
		prs->d++;
		while ((s[prs->d] && s[prs->d] != '$')
			|| (s[prs->d] && s[prs->d] == '$' && !ft_dol(s, prs->d, prs)))
			prs->d++;
	}
	prs->len_str[1] = prs->d -1;
	if (s[prs->d] != ' ' && prs->d >= (int)(ft_strlen(s) -1))
	{
		prs->len_dollar[0] = -1;
		return ;
	}
	prs->len_dollar[0] = prs->d +1;
	while (s[prs->d] != '\0' && s[prs->d] != ' ')
		prs->d++;
	prs->len_dollar[1] = prs->d -1;
}

int	ft_check_after_key(char *key)
{
	int		i;
	int		check_isalnum;

	check_isalnum = 0;
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i])
			&& key[i] != '<' && key[i] != '>' && key[i] != '_')
		{
			check_isalnum = 1;
			break ;
		}
		i++;
	}
	if (check_isalnum)
		return (i);
	return (0);
}

int	ft_check_is_in(char *str, int index, t_parser *parser)
{
	char	*sub;

	sub = ft_substr(str, 0, index);
	if (ft_qcheck(sub, index, parser) == 2)
	{
		free(sub);
		sub = NULL;
		return (1);
	}
	free(sub);
	sub = NULL;
	return (0);
}

int	ft_check_special(char *str, int i)
{
	char	*sub;
	int		start;

	start = 0;
	sub = NULL;
	if ((str[i] > 36 && str[i] < 48 && str[i] != '*')
		|| (str[i] > 57 && str[i] <= 62)
		|| (str[i] > 122 && str[i] < 127)
		|| (str[i] > 90 && str[i] < 97))
		return (0);
	else if (str[i] == '$')
	{
		start = i;
		while (str[i] && str[i] != ' ')
			i++;
		sub = ft_substr(str, start, (i - start));
		i = -1;
		while (sub[++i])
			if (ft_isalnum(sub[i]) || sub[i] == '_')
				start = -1;
		free(sub);
		if (start != -1)
			return (0);
	}
	return (1);
}
