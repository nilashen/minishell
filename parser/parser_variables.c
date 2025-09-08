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
			if (str[i] == '$' && ft_is_dollar(str, i, parser))
				count_dollar++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count_dollar);
}

int	ft_is_dollar(char *str, int i, t_parser *parser)
{
	char	*check_str;
	int		dval;
	int		sval;
	int		start;

	start = 0;
	if (str[i] == '$' && str[i +1] != '\0' && str[i +1] != ' '
		&& str[i +1] != '"' && str[i +1] != '\'' && ft_check_special(str, i +1))
	{
		start = i;
		while (str[i] && (str[i] != ' ' || (str[i] == ' '
					&& ft_quote_check(str, i, parser))))
			i++;
		check_str = ft_substr(str, start, (i - start));
		dval = ft_count_quote(check_str, i - start, '"') % 2;
		sval = ft_count_quote(check_str, i - start, '\'') % 2;
		if ((dval && sval && check_str[i - start -1] != '\'')
			|| (!dval && !sval) || (dval && !sval)
			|| (sval && ft_check_is_in(str, i, parser)))
			start = -1;
		free(check_str);
	}
	if (start == -1)
		return (1);
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
