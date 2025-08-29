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
}

static int	ft_handle_quote_checks(char **tmp, t_parser *prs)
{
	if (prs->check == 2 && ft_quote_count_check(*tmp, &prs->check, '"', 2))
	{
		*tmp = NULL;
		return (2);
	}
	if (prs->check == 1 && ft_quote_count_check(*tmp, &prs->check, '\'', 1))
	{
		*tmp = NULL;
		return (1);
	}
	if (prs->check == 2 || prs->check == 1)
		*tmp = NULL;
	return (0);
}

static int	ft_quote_handler(char *str, char *tmp, int len, t_parser *prs)
{
	int	result;

	while (str[++prs->k] && prs->k < len)
	{
		ft_quote_handler_helper(str, &tmp, len, prs);
		if (prs->check_if && str[prs->k] == '"'
			&& (!str[prs->k + 1] || (str[prs->k +1] && str[prs->k +1] == ' '))
			&& (ft_count_quote(str, prs->k +1, '"') - prs->count_dq) % 2 != 0)
			return (2);
		else if (prs->check_if && str[prs->k] == '\''
			&& (!str[prs->k +1] || (str[prs->k + 1] && str[prs->k +1] == ' '))
			&& (ft_count_quote(str, prs->k + 1, '\'') - prs->count_sq) % 2 != 0)
			return (1);
		result = ft_handle_quote_checks(&tmp, prs);
		if (result)
			return (result);
		prs->check_if = 1;
	}
	return (0);
}

int	ft_quote_check(char *str, int len, t_parser *prs)
{
	char	*tmp;
	char	*new_str;
	int		result;

	new_str = ft_substr(str, 0, (size_t)len);
	tmp = NULL;
	ft_init_paremeter(prs);
	result = ft_quote_handler(new_str, tmp, len, prs);
	free(new_str);
	return (result);
}