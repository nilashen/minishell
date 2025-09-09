/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_output_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:52:33 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:15:56 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_right_redirect(char *str, int len, t_parser *pars)
{
	t_node	*new_node;
	char	*sub;
	char	*join;

	sub = ft_substr(str, pars->nr, len - pars->nr);
	join = ft_strjoin(sub, " ");
	new_node = ft_new_node(join);
	ft_node_add_back(&pars->sublist, new_node);
	pars->nr = len;
	pars->r = pars->nr;
	pars->check_redirect++;
	free(sub);
	return (1);
}

static void	ft_heradoc_handler(char *str, t_parser *prs)
{
	if (str[prs->r] == '<' && !ft_qcheck(str, prs->r, prs)
		&& (str[prs->r +1] && str[prs->r +1] == '<')
		&& prs->r -1 >= 0 && str[prs->r -1] != ' ')
		ft_left_redirect(str, prs->r, 'h', prs);
	if (str[prs->r] == '<' && !ft_qcheck(str, prs->r, prs)
		&& (str[prs->r +1] && str[prs->r +1] == '<')
		&& str[prs->r +2] && str[prs->r +2] != ' ')
		ft_right_redirect(str, (++prs->r +1), prs);
	ft_check_control(prs);
	if (str[prs->r] == '>' && !ft_qcheck(str, prs->r, prs)
		&& (str[prs->r +1] && str[prs->r +1] == '>')
		&& prs->r -1 >= 0 && str[prs->r -1] != ' ')
		ft_left_redirect(str, prs->r, 'h', prs);
	if (str[prs->r] == '>' && !ft_qcheck(str, prs->r, prs)
		&& (str[prs->r +1] && str[prs->r +1] == '>')
		&& str[prs->r +2] && str[prs->r +2] != ' ')
		ft_right_redirect(str, (++prs->r +1), prs);
	ft_check_control(prs);
}

static t_node	*ft_redirect_handler(char *str, t_parser *prs)
{
	prs->sublist = NULL;
	while (str[++prs->r])
	{
		ft_heradoc_handler(str, prs);
		if (str[prs->r] == '>' && !ft_qcheck(str, prs->r, prs)
			&& str[prs->r +1] && str[prs->r +1] != '>'
			&& prs->r -1 >= 0 && str[prs->r -1] != ' ' && str[prs->r -1] != '>')
			ft_left_redirect(str, prs->r, 'r', prs);
		if (str[prs->r] == '>' && !ft_qcheck(str, prs->r, prs)
			&& str[prs->r +1] && str[prs->r +1] != ' ' && str[prs->r +1] != '>')
			ft_right_redirect(str, prs->r +1, prs);
		ft_check_control(prs);
		if (str[prs->r] == '<' && !ft_qcheck(str, prs->r, prs)
			&& str[prs->r + 1] && str[prs->r +1] != '<'
			&& prs->r -1 >= 0 && str[prs->r -1] != ' ' && str[prs->r -1] != '<')
			ft_left_redirect(str, prs->r, 'r', prs);
		if (str[prs->r] == '<' && !ft_qcheck(str, prs->r, prs)
			&& str[prs->r +1] && str[prs->r +1] != ' ' && str[prs->r +1] != '<')
			ft_right_redirect(str, prs->r +1, prs);
		ft_check_control(prs);
	}
	if (!prs->check_redirect)
		return (ft_new_node(ft_strdup(str)));
	return (ft_finish_redirect(str, prs->r, prs));
}

char	**ft_redirect_parser(t_parser *pars, t_node *list)
{
	int		i;
	t_node	*new_node;

	list = NULL;
	i = -1;
	while (pars->cleaned[++i])
	{
		pars->r = -1;
		pars->nr = 0;
		pars->control = 0;
		pars->check_redirect = 0;
		if (ft_count_real_char(pars->cleaned[i], '>', pars)
			|| ft_count_real_char(pars->cleaned[i], '<', pars))
			new_node = ft_redirect_handler(pars->cleaned[i], pars);
		else
			new_node = ft_new_node(ft_strdup(pars->cleaned[i]));
		ft_node_add_back(&list, new_node);
	}
	return (ft_node_to_double(&list, 0, 0));
}

char	**ft_node_to_double(t_node **list, int i, int list_size)
{
	char	**dest;
	t_node	*tmp;
	t_node	*tmp2;

	tmp = *list;
	list_size = ft_listlen(*list);
	dest = malloc(sizeof(char *) * (list_size + 1));
	if (!dest)
		return (NULL);
	dest[list_size] = NULL;
	while (tmp)
	{
		dest[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	tmp = *list;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp2->str);
		tmp = tmp->next;
		free(tmp2);
	}
	return (dest);
}
