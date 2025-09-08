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
