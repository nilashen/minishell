/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:21:12 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 17:15:27 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_extract_braced_var(char *str, int *consumed)
{
	int		i;
	int		start;
	char	*var_name;

	i = 0;
	*consumed = 0;
	if (str[i] != '{')
		return (NULL);
	i++;
	start = i;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] != '}')
		return (NULL);
	var_name = ft_substr(str, start, i - start);
	*consumed = i + 1;
	return (var_name);
}

char	*ft_find_env_braced(char *str, int n, t_parser *parser, t_env *env)
{
	char	*dest;
	char	*var_name;
	int		consumed;

	dest = NULL;
	if (str[0] == '{')
	{
		var_name = ft_extract_braced_var(str, &consumed);
		if (var_name)
		{
			dest = ft_dup_key(var_name, parser, env);
			free(var_name);
			return (dest);
		}
		return (ft_substr(str, 0, n));
	}
	return (NULL);
}

char	*ft_find_env_key(char *str, int n, t_parser *parser, t_env *env)
{
	char	*dest;

	dest = NULL;
	parser->key = ft_substr(str, 0, n);
	if (!parser->key || !str)
		return (NULL);
	if (ft_isdigit(parser->key[0]) || parser->key[0] == '@'
		|| parser->key[0] == '*')
		dest = ft_strdup(parser->key + 1);
	else if (parser->key[0] == '$' && !ft_strchr(parser->key + 1, '$'))
		dest = ft_strdup(parser->key);
	else if (parser->key[0] == '$' && ft_strchr(parser->key + 1, '$'))
		dest = ft_refind_env(parser, env);
	else if (parser->key[0] != '$' && ft_strchr(parser->key + 1, '$'))
		dest = ft_united_dollar(parser, env);
	else if (!ft_check_after_key(parser->key))
		dest = ft_dup_key(parser->key, parser, env);
	else
		dest = ft_join_key(parser->key, ft_check_after_key(parser->key), env);
	free(parser->key);
	return (dest);
}

int	ft_process_dollar_token(char *str, t_parser *prs,
	t_env *env, t_node **dollar)
{
	char	*env_result;
	t_node	*new_node;

	ft_pars_str(str, prs);
	env_result = ft_env_handler(str, env, prs);
	if (!env_result)
		env_result = ft_strdup("");
	if (!env_result)
		return (0);
	new_node = ft_new_node(env_result);
	if (!new_node)
	{
		free(env_result);
		return (0);
	}
	ft_node_add_back(dollar, new_node);
	return (1);
}
