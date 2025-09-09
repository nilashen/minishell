/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:50:55 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 15:50:56 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_new_node(char *content)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->str = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_node_add_back(t_node **lst, t_node *new_node)
{
	t_node	*temp;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

char	*ft_new_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	lens1;
	char	*dst;

	lens1 = ft_strlen(s1);
	i = -1;
	dst = malloc(sizeof(char) * (lens1 + ft_strlen(s2) + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[++i])
		dst[i] = (char )s1[i];
	i = -1;
	while (s2[++i])
	{
		dst[lens1] = s2[i];
		lens1++;
	}
	dst[lens1] = '\0';
	free(s1);
	return (dst);
}

char	*ft_node_resizer(t_node *dollar)
{
	char	*dest;
	t_node	*tmp;
	t_node	*tmp2;

	tmp = dollar;
	dest = ft_strdup("");
	while (tmp)
	{
		dest = ft_new_strjoin(dest, tmp->str);
		tmp = tmp->next;
	}
	tmp = dollar;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp2->str);
		tmp = tmp->next;
		free(tmp2);
	}
	return (dest);
}
