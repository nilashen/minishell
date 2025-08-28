#include "../includes/minishell.h"

void	env_addback(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp ->next = new;
}

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*get_env(t_state *data, char **env)
{
	int		i;
	int		x;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	(void)data;
	while (env[i])
	{
		x = 0;
		while (env[i][x] && env[i][x] != '=')
			x++;
		env_addback(&tmp, new_env(ft_substr(env[i], 0, x),
				ft_substr(env[i], x + 1, ft_strlen(env[i]) - x - 1)));
		i++;
	}
	return (tmp);
}

void	ft_sep_path(t_state *state)
{
	t_env	*tmp;

	tmp = state->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH",
				ft_strlen(tmp->key)) == 0)
		{
			state->sep_path = ft_split(tmp->value, ':');
			return ;
		}
		tmp = tmp->next;
	}
	state->sep_path = ft_split("", ':');
}
