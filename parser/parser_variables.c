/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:53:36 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:20:47 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_dollar(char *str, t_parser *parser)
{
	int	i;
	int	count_dollar;

	count_dollar = 0;
	if (ft_strchr(str, '$') != NULL && ft_strlen(str) > 1)
	{
		i = 0;
		while (str[i])
		{
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' && ft_dol(str, i, parser))
				count_dollar++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count_dollar);
}

int	ft_dol(char *str, int i, t_parser *parser)
{
	if (str[i] != '$' || str[i + 1] == '\0' || str[i + 1] == ' ')
		return (0);
	if (ft_is_braced_dollar(str, i))
		return (1);
	if (str[i + 1] != '"' && str[i + 1] != '\'' && ft_check_special(str, i + 1))
	{
		if (ft_is_valid_dollar(str, i, parser))
			return (1);
	}
	return (0);
}

static char	*ft_put_refind(t_parser *parser, t_env *env, char *tmp)
{
	char	*united;
	char	*dest;

	united = NULL;
	if (ft_isdigit(parser->key[0])
		|| parser->key[0] == '@' || parser->key[0] == '*')
		united = ft_strdup(parser->key + 1);
	else if (ft_strchr(parser->key, '$'))
		united = ft_united_dollar(parser, env);
	else if (!ft_check_after_key(parser->key))
		united = ft_dup_key(parser->key, parser, env);
	else
		united = ft_join_key(parser->key, ft_check_after_key(parser->key), env);
	dest = ft_strjoin(tmp, united);
	free(united);
	free(tmp);
	return (dest);
}

char	*ft_refind_env(t_parser *parser, t_env *env)
{
	char	*tmp;
	char	*tmp_key;
	int		i;
	int		start;
	int		len;

	i = 0;
	start = i ;
	while (parser->key[i] && parser->key[i] == '$')
		i++;
	while (parser->key[i] && parser->key[i] != '$')
		i++;
	len = i;
	if (parser->key[0] == '$')
	{
		while (parser->key[i] == '$')
			i++;
		i--;
	}
	tmp = ft_substr(parser->key, start, (len - start));
	tmp_key = ft_strdup(parser->key + i + 1);
	free(parser->key);
	parser->key = ft_strdup(tmp_key);
	free(tmp_key);
	return (ft_put_refind(parser, env, tmp));
}
