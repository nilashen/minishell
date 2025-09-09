/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:37:55 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:20:47 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_env(char *str, int n, t_parser *parser, t_env *env)
{
	char	*dest;

	dest = ft_find_env_braced(str, n, parser, env);
	if (dest)
		return (dest);
	return (ft_find_env_key(str, n, parser, env));
}

char	*ft_env_handler(char *str, t_env *env, t_parser *parser)
{
	char	*tmp_str;
	char	*env_str;
	char	*dest;
	int		str_len;
	int		dolrlen;

	str_len = (parser->len_str[1] - parser->len_str[0] + 1);
	dolrlen = (parser->len_dollar[1] - parser->len_dollar[0] + 1);
	if (parser->len_str[0] == -1)
		tmp_str = ft_strdup("");
	else
		tmp_str = ft_substr(str, parser->len_str[0], str_len);
	if (parser->len_dollar[0] == -1)
		env_str = ft_strdup("");
	else
		env_str = ft_env(str + parser->len_dollar[0], dolrlen, parser, env);
	if (parser->dollar_is_first)
		dest = ft_strjoin(env_str, tmp_str);
	else
		dest = ft_strjoin(tmp_str, env_str);
	free(tmp_str);
	free(env_str);
	return (dest);
}

char	*ft_dol_handler(char *str, t_node *dollar, t_parser *prs, t_env *env)
{
	if (!str || !prs)
		return (NULL);
	dollar = NULL;
	prs->d = 0;
	while (str[prs->d])
	{
		if (str[prs->d] == '$' && ft_dol(str, prs->d, prs))
			prs->dollar_is_first = 1;
		else
			prs->dollar_is_first = 0;
		if (!ft_process_dollar_token(str, prs, env, &dollar))
			return (NULL);
	}
	return (ft_node_resizer(dollar));
}

char	*ft_join_key(char *key, int index, t_env *env)
{
	char	*new_key;
	char	*after_key;
	char	*dest;

	new_key = ft_substr(key, 0, index);
	after_key = ft_substr(key, index, ft_strlen(key));
	while (env != NULL)
	{
		if (ft_strncmp(new_key, env->key, ft_strlen(env->key)) == 0
			&& ft_strlen(env->key) == ft_strlen(new_key))
		{
			dest = ft_strjoin(env->value, after_key);
			free(new_key);
			free(after_key);
			return (dest);
		}
		env = env->next;
	}
	free(new_key);
	return (after_key);
}

char	*ft_dup_key(char *key, t_parser *pars, t_env *env)
{
	char	*quest;
	char	*result;

	if (key[0] == '#')
	{
		key[0] = '0';
		return (ft_strdup(key));
	}
	else if (key[0] == '?')
	{
		quest = ft_itoa(*(pars->ptr_errno));
		result = ft_strjoin(quest, key +1);
		free(quest);
		return (result);
	}
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, ft_strlen(env->key)) == 0
			&& ft_strlen(env->key) == ft_strlen(key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
