#include "../includes/minishell.h"

static int	ft_quote_count_check(char *str, int *check,
	char quote_type, int num)
{
	if (*check == num && str != NULL)
	{
		if (ft_count_quote(str, (int)ft_strlen(str), quote_type) % 2 != 0)
		{
			free(str);
			return (1);
		}
		else
		{
			free(str);
			*check = 0;
			return (0);
		}
	}
	return (0);
}

static void	ft_quote_handler_helper(char *str, char **tmp,
	int len, t_parser *prs)
{
	int	dq;
	int	sq;

	dq = (ft_count_quote(str, prs->k, '"') - prs->count_dq) % 2;
	sq = (ft_count_quote(str, prs->k, '\'') - prs->count_sq) % 2;
	if ((str[prs->k] == '"' && str[prs->k +1]) && prs->check == 0
		&& (!sq || (ft_count_quote(str, prs->k, '"') > 0 && !dq && sq)))
	{
		prs->m = prs->k;
		*tmp = ft_cut_dquote(str, len, prs);
		prs->check_if = 0;
	}
	else if ((str[prs->k] == '\'' && str[prs->k +1]) && prs->check == 0
		&& (!dq || (ft_count_quote(str, prs->k, '\'') > 0 && !sq && dq)))
	{
		*tmp = ft_cut_squote(str, len, prs);
		prs->check_if = 0;
	}
	else
		(void)tmp;
}

static int	ft_quote_handler(char *str, char *tmp, int len, t_parser *prs)
{
	while (str[++prs->k] && prs->k < len)
	{
		ft_quote_handler_helper(str, &tmp, len, prs);
		if (prs->check_if && str[prs->k] == '"'
			&& (!str[prs->k + 1] || (str[prs->k +1] && str[prs->k +1] == ' ' ))
			&& (ft_count_quote(str, prs->k +1, '"') - prs->count_dq) % 2 != 0)
			return (2);
		else if (prs->check_if && str[prs->k] == '\''
			&& (!str[prs->k +1] || (str[prs->k + 1] && str[prs->k +1] == ' ' ))
			&& (ft_count_quote(str, prs->k + 1, '\'') - prs->count_sq) % 2 != 0)
			return (1);
		if (prs->check == 2 && ft_quote_count_check(tmp, &prs->check, '"', 2))
			return (2);
		if (prs->check == 1 && ft_quote_count_check(tmp, &prs->check, '\'', 1))
			return (1);
		prs->check_if = 1;
	}
	if (tmp)
		free(tmp);
	return (0);
}

int	ft_quote_check(char *str, int len, t_parser *pars)
{
	char	*tmp;
	int		result;

	tmp = NULL;
	ft_init_paremeter(pars);
	result = ft_quote_handler(str, tmp, len, pars);
	if (tmp != NULL)
		free(tmp);
	return (result);
}
