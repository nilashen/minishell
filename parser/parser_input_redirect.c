/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:48:49 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 15:48:50 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_left_redirect(char *str, int len, char type, t_parser *pars)
{
	t_node	*new_node;
	char	*sub;
	char	*join;
	char	*result;
	char	*sub2;

	result = NULL;
	sub = ft_substr(str, pars->nr, len - pars->nr);
	if (type == 'h')
	{
		sub2 = ft_substr(str, len, 2);
		join = ft_strjoin(sub, " ");
		result = ft_strjoin(join, sub2);
		pars->nr = len + 2;
	}
	else if (type == 'r')
	{
		sub2 = ft_substr(str, len, 1);
		join = ft_strjoin(sub, " ");
		result = ft_strjoin(join, sub2);
		pars->nr = len + 1;
	}
	ft_free_substr(&sub, &sub2, &join, pars);
	new_node = ft_new_node(result);
	ft_node_add_back(&pars->sublist, new_node);
}

t_node	*ft_finish_redirect(char *str, int i, t_parser *pars)
{
	t_node	*new_node;
	t_node	*dest;
	char	*sub;
	char	*restr;

	if (i != pars->nr)
	{
		sub = ft_substr(str, pars->nr, i - pars->nr);
		new_node = ft_new_node(sub);
		ft_node_add_back(&pars->sublist, new_node);
	}
	restr = ft_node_resizer(pars->sublist);
	dest = ft_new_node(restr);
	return (dest);
}

int	ft_check_redirect_char(char *str, int len)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 1 && (str[0] == '"' || str[0] == '\''))
		return (1);
	else if (!ft_check_full_char(str, ' ', len))
		return (1);
	while (i < len && str[i])
	{
		if (str[i] == '>' || str[i] == ' ' || str[i] == '<')
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_check_control(t_parser *parser)
{
	if (parser->control)
	{
		parser->r = parser->nr;
		parser->control = 0;
	}
}

void	ft_free_substr(char **sub, char **sub2, char **sub3, t_parser *pars)
{
	pars->control = ++pars->check_redirect;
	free (*sub);
	sub = NULL;
	free (*sub2);
	sub2 = NULL;
	free(*sub3);
	sub3 = NULL;
}
