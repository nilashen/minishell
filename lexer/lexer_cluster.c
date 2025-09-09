/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cluster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:36:56 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:36:57 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_clean_cmd(char **str)
{
	int		i;
	int		j;
	char	**dest;

	dest = malloc(sizeof(char *) * (ft_double_str_len(str) +1));
	dest[ft_double_str_len(str)] = NULL;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((ft_strchr(str[i], '>') || ft_strchr(str[i], '<'))
			&& (ft_strchr(str[i], '"') || ft_strchr(str[i], '\'')))
			dest[j++] = ft_substr(str[i], 1, ft_strlen(str[i]) - 2);
		else
			dest[j++] = ft_strdup(str[i]);
	}
	ft_free_double_str(str);
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

static void	ft_cluster_addback(t_cluster **cluster_node, t_cluster *new)
{
	t_cluster	*tmp;

	if (!cluster_node || !new)
		return ;
	if (!*cluster_node)
	{
		*cluster_node = new;
		return ;
	}
	tmp = *cluster_node;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp ->next = new;
}

static t_cluster	*ft_new_cluster_node(char	**arg)
{
	t_cluster	*new;

	new = (t_cluster *)malloc(sizeof(t_cluster));
	new->cmd = ft_clean_cmd(ft_fill_cmd(arg));
	new->files = ft_new_files_node(arg, -1);
	if (new->files->heredoc[0] != '\0' && new->files->fd_input < 2)
		new->files->fd_input = -2;
	new->pid = -1;
	new->next = NULL;
	if (new->files->error == 2)
		return (ft_file_open_error(new, new->files->output));
	if (new->files->error == 1)
		return (ft_file_open_error(new, new->files->input));
	if (new->files->error == 3)
	{
		ft_cluster_free(new);
		return (NULL);
	}
	return (new);
}

void	ft_cluster(t_state *state)
{
	t_cluster	*new;
	char		***third_arg;
	t_cluster	*tmp_node;
	int			i;

	i = 0;
	tmp_node = NULL;
	third_arg = state->third_arg_clean;
	while (third_arg[i])
	{
		new = ft_new_cluster_node(third_arg[i]);
		if (new == NULL)
			state->error = 1;
		ft_cluster_addback(&tmp_node, new);
		i++;
	}
	state->cluster = tmp_node;
}
