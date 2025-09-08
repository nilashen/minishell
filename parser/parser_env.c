#include "../includes/minishell.h"

static char	*ft_find_env(char *str, int n, t_parser *parser, t_env *env)
{
	char	*dest;

	dest = NULL;
	parser->key = ft_substr(str, 0, n);
	if (!parser->key || !str)
		return (NULL);
	if (ft_isdigit(parser->key[0])
		|| parser->key[0] == '@' || parser->key[0] == '*')
		dest = ft_strdup(parser->key + 1);
	else if (parser->key[0] == '$' && !ft_strchr(parser->key + 1, '$'))
		dest = ft_strdup(parser->key);
	else if (parser->key[0] == '$' && ft_strchr(parser->key + 1, '$'))
		dest = ft_refind_env(parser, env);
	else if (parser->key[0] != '$' && ft_strchr(parser->key + 1, '$'))
		dest = ft_united_dolar(parser, env);
	else if (!ft_check_after_key(parser->key))
		dest = ft_dup_key(parser->key, parser, env);
	else
		dest = ft_join_key(parser->key, ft_check_after_key(parser->key), env);
	free(parser->key);
	return (dest);
}

static char	*ft_env_handler(char *str, t_env *env, t_parser *parser)
{
	char	*tmp_str;
	char	*env_str;
	char	*dest;
	int		str_len;
	int		dolrlen;

	str_len = (parser->len_str[1] - parser->len_str[0] + 1);
	dolrlen = (parser->len_dolar[1] - parser->len_dolar[0] + 1);
	if (parser->len_str[0] == -1)
		tmp_str = ft_strdup("");
	else
		tmp_str = ft_substr(str, parser->len_str[0], str_len);
	if (parser->len_dolar[0] == -1)
		env_str = ft_strdup("");
	else
		env_str = ft_find_env(str + parser->len_dolar[0], dolrlen, parser, env);
	if (parser->dolar_is_first)
		dest = ft_strjoin(env_str, tmp_str);
	else
		dest = ft_strjoin(tmp_str, env_str);
	free(tmp_str);
	free(env_str);
	return (dest);
}

char	*ft_dolar_handler(char *str, t_node *dolar, t_parser *prs, t_env *env)
{
	t_node	*new_node;

	dolar = NULL;
	prs->d = 0;
	while (str[prs->d])
	{
		if (str[prs->d] == '$' && ft_is_dollar(str, prs->d, prs))
			prs->dolar_is_first = 1;
		else
			prs->dolar_is_first = 0;
		ft_pars_str(str, prs);
		new_node = ft_new_node(ft_env_handler(str, env, prs));
		if (!new_node)
			return (NULL);
		ft_node_add_back(&dolar, new_node);
	}
	return (ft_node_resizer(dolar));
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
