/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expand_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:08:10 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:17:06 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_double_quote_check(int **chk_dq, char **tmp,
				t_parser *prs, int len)
{
	if (**chk_dq)
		*tmp = ft_strdup(prs->key + len - 2);
}

int	ft_split_key_by_quotes(t_parser *prs, int len)
{
	char	*sub;
	int		check_sub;

	check_sub = 0;
	if (prs->key[len - 1] == '"' && len - 2 >= 0
		&& prs->key[len - 2] != '$')
	{
		sub = ft_substr(prs->key, 0, len - 1);
		if (!sub)
			return (-1);
		check_sub = 1;
		prs->united_key = ft_split(sub, '$');
		free(sub);
	}
	else
		prs->united_key = ft_split(prs->key, '$');
	return (check_sub);
}

int	ft_allocate_united_env(t_parser *prs, int count)
{
	prs->united_env = malloc(sizeof(char *) * (count + 1));
	if (!prs->united_env)
	{
		ft_free_double_str(prs->united_key);
		return (0);
	}
	prs->united_env[count] = NULL;
	return (1);
}

int	ft_is_braced_dollar(char *str, int i)
{
	int	temp_i;

	if (str[i + 1] != '{')
		return (0);
	temp_i = i + 2;
	while (str[temp_i] && str[temp_i] != '}')
		temp_i++;
	return (str[temp_i] == '}');
}

int	ft_is_valid_dollar(char *str, int i, t_parser *parser)
{
	char	*check_str;
	int		start;
	int		dval;
	int		sval;

	start = i;
	while (str[i]
		&& (str[i] != ' ' || (str[i] == ' ' && ft_qcheck(str, i, parser))))
	{
		i++;
	}
	check_str = ft_substr(str, start, i - start);
	if (!check_str)
		return (0);
	dval = ft_count_quote(check_str, i - start, '"') % 2;
	sval = ft_count_quote(check_str, i - start, '\'') % 2;
	if ((dval && sval && check_str[i - start - 1] != '\'')
		|| (!dval && !sval) || (dval && !sval)
		|| (sval && ft_check_is_in(str, i, parser)))
	{
		free(check_str);
		return (1);
	}
	free(check_str);
	return (0);
}
