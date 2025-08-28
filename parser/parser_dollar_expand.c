#include "../includes/minishell.h"

static int	ft_mini_dolar_counter(char *str, int ***chck_dolr, int ***chck_dq)
{
	int		i;
	int		count_dolr;
	int		len;

	len = (ft_strlen(str) -1);
	if (str[len] == '$')
		***chck_dolr = 1;
	else if (str[len] == '"' && len -1 >= 0 && str[len -1] == '$')
		***chck_dq = 1;
	count_dolr = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i +1] != '$')
		{
			if (***chck_dolr == 1 && i == len)
				break ;
			count_dolr++;
		}
	}
	return (count_dolr + 1);
}

static int	ft_init_united(int **chk_dq, int **chk_dolr, char **tmp,
	t_parser *prs)
{
	int		count;
	int		len;
	int		check_sub;
	char	*sub;

	check_sub = 0;
	len = ft_strlen(prs->key);
	count = ft_mini_dolar_counter(prs->key, &chk_dolr, &chk_dq);
	if (**chk_dq)
		*tmp = ft_strdup(prs->key + len -2);
	if (prs->key[len -1] == '"' && len - 2 >= 0
		&& prs->key[len -2] != '$')
	{
		sub = ft_substr(prs->key, 0, len -1);
		check_sub = 1;
		prs->united_key = ft_split(sub, '$');
		free(sub);
	}
	else
		prs->united_key = ft_split(prs->key, '$');
	prs->united_env = malloc(sizeof(char *) * (count +1));
	if (!prs->united_env)
		return (0);
	prs->united_env[count] = NULL;
	return (check_sub);
}

static char	*ft_put_united_env(char *key, t_parser *pars, t_env *env)
{
	if (!key)
		return (NULL);
	if (ft_isdigit(key[0])
		|| key[0] == '@' || key[0] == '*')
		return (ft_strdup(key + 1));
	else if (!ft_check_after_key(key))
		return (ft_dup_key(key, pars, env));
	else
		return (ft_join_key(key, ft_check_after_key(key), env));
}

static void	ft_united_handler(int *chk_dq, int *chk_dlr,
	t_parser *prs, t_env *env)
{
	int		i;
	int		check_sub;
	char	*tmp;

	*chk_dq = 0;
	*chk_dlr = 0;
	check_sub = 0;
	i = -1;
	check_sub = ft_init_united(&chk_dq, &chk_dlr, &tmp, prs);
	while (prs->united_key[++i])
		prs->united_env[i] = ft_put_united_env(prs->united_key[i], prs, env);
	i--;
	if (*chk_dq)
	{
		prs->united_env[i] = ft_new_strjoin(prs->united_env[i], tmp);
		free(tmp);
	}
	else if (check_sub)
		prs->united_env[i] = ft_new_strjoin(prs->united_env[i], "\"");
	else if (*chk_dlr)
		prs->united_env[i] = ft_new_strjoin(prs->united_env[i], "$");
}

char	*ft_united_dolar(t_parser *parser, t_env *env)
{
	char	*dest;
	int		chck_dolr;
	int		chck_dq;

	ft_united_handler(&chck_dq, &chck_dolr, parser, env);
	dest = ft_resizer(parser->united_env);
	ft_free_double_str(parser->united_key);
	return (dest);
}
