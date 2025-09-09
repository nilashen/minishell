/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:53:13 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:15:56 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_tilde_handler(char *tmp, char *str, int *index, t_env *env)
{
	char	*home;
	char	*dest;
	int		check_home;

	check_home = 1;
	while (env && check_home)
	{
		if (!ft_strncmp(env->key, "HOME", ft_strlen("HOME"))
			&& ft_strlen("HOME") == ft_strlen(env->key))
		{
			home = ft_strdup(env->value);
			check_home = 0;
			break ;
		}
		env = env->next;
	}
	if (check_home)
		home = ft_strdup("");
	dest = ft_strjoin(tmp, home);
	if (*index + 1 == (int)(ft_strlen(str) -1))
		dest = ft_new_strjoin(dest, str + (++(*index)));
	free(home);
	free(tmp);
	return (dest);
}

static char	*ft_check_tilde(char *str, int i, t_parser *prs, t_env *env)
{
	char	*tmp;
	int		point;
	t_node	*tilde_line;

	tilde_line = NULL;
	point = 0;
	while (str[++i])
	{
		if (str[i] == '~' && !ft_qcheck(str, i, prs)
			&& ((str[i +1] && (str[i +1] == '/' || str[i +1] == ' '))
				|| str[i +1] == '\0') && ((i -1 >= 0 && (str[i -1] == ' '))
				|| !i))
		{
			tmp = ft_substr(str, point, i - point);
			point = i +1;
			ft_node_add_back(&tilde_line,
				ft_new_node(ft_tilde_handler(tmp, str, &i, env)));
		}
		if (i == (int)ft_strlen(str) - 1 && point != i)
			ft_node_add_back(&tilde_line,
				ft_new_node(ft_substr(str, point, i - point + 1)));
	}
	return (ft_node_resizer(tilde_line));
}

char	**ft_put_tilde(char **str, t_state *state, t_parser *parser)
{
	int		i;
	t_node	*new_node;
	t_node	*tilde;
	t_env	*env;

	tilde = NULL;
	i = -1;
	env = state->env;
	while (str[++i])
	{
		if (ft_count_real_char(str[i], '~', parser))
			new_node = ft_new_node(ft_check_tilde(str[i], -1, parser, env));
		else
			new_node = ft_new_node(ft_strdup(str[i]));
		ft_node_add_back(&tilde, new_node);
	}
	return (ft_node_to_double(&tilde, 0, 0));
}
