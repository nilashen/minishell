/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:36:30 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:15:56 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_first(char *str, char keycode, int i, t_parser *pars)
{
	i = 0;
	if (keycode == '"')
	{
		while (str[++i])
		{
			if (((str[i +1] != '\0' && str[i +1] == ' ') || str[i +1] == '\0')
				&& ft_qcheck(str, i +1, pars) == 0 && str[i] == '"')
				return (2);
			else if (str[i] == ' ' && ft_qcheck(str, i, pars) == 0)
				break ;
		}
	}
	else if (keycode == '\'')
	{
		while (str[++i])
		{
			if (((str[i + 1] != '\0' && str[i +1] == ' ') || str[i +1] == '\0')
				&& ft_qcheck(str, i + 1, pars) == 0 && str[i] == '\'')
				return (1);
			else if (str[i] == ' ' && ft_qcheck(str, i, pars) == 0)
				break ;
		}
	}
	return (0);
}

static int	ft_write_in_quote(char *str, char cod, char q, t_parser *prs)
{
	int	c;

	c = 0;
	if (cod == 'F')
		prs->cleaned[prs->i][prs->j++] = str[c];
	while (str[++c])
	{
		if (str[c] == ' ' && ft_qcheck(str, c, prs) == 0)
			return (--c);
		if (str[c] == q && ft_qcheck(str, c +1, prs) == 0
			&& cod != 'F')
			break ;
		if (str[c] != q)
			prs->cleaned[prs->i][prs->j++] = str[c];
		else if ((str[c] == q && ((str[c +1] && str[c +1] == ' ') || !str[c +1])
				&& !ft_qcheck(str, c +1, prs)) && cod == 'F')
		{
			prs->cleaned[prs->i][prs->j++] = str[c];
			break ;
		}
	}
	return (c);
}

static void	ft_cleaner_helper(t_parser *prs, int *i)
{
	if ((prs->src[prs->i][*i] == '"'
		&& (((*i -1 >= 0 && prs->src[prs->i][*i -1] == ' ') || *i == 0)
		&& ft_qcheck(prs->src[prs->i], *i, prs) == 0))
		&& ft_is_first(prs->src[prs->i] + *i, '"', *i, prs) == 2)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'F', '"', prs);
	else if ((prs->src[prs->i][*i] == '\''
		&& (((*i -1 >= 0 && prs->src[prs->i][*i -1] == ' ') || *i == 0)
		&& ft_qcheck(prs->src[prs->i], *i, prs) == 0))
		&& ft_is_first(prs->src[prs->i] + *i, '\'', *i, prs) == 1)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'F', '\'', prs);
	else if (prs->src[prs->i][*i] == '"'
		&& ft_qcheck(prs->src[prs->i], *i +1, prs) == 2)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'N', '"', prs);
	else if (prs->src[prs->i][*i] == '\''
		&& ft_qcheck(prs->src[prs->i], *i +1, prs) == 1)
		*i += ft_write_in_quote(prs->src[prs->i] + *i, 'N', '\'', prs);
	else
		prs->cleaned[prs->i][prs->j++] = prs->src[prs->i][*i];
	return ;
}

static void	ft_cleaner(t_parser *pars, int i)
{
	while (pars->src[pars->i][++i])
	{
		if (pars->src[pars->i][i] == ' '
			&& ft_qcheck(pars->src[pars->i], i, pars) == 0)
		{
			pars->cleaned[pars->i][pars->j++] = pars->src[pars->i][i];
			while (pars->src[pars->i][i] == ' ')
				i++;
			i--;
		}
		else
			ft_cleaner_helper(pars, &i);
	}
	pars->cleaned[pars->i][pars->j] = '\0';
}

void	ft_send_cleaner(t_parser *parser)
{
	parser->i = -1;
	while (parser->src[++parser->i])
	{
		parser->j = 0;
		ft_cleaner(parser, -1);
	}
}
