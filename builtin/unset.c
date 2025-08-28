#include "../includes/minishell.h"

static int	ft_value_check(t_state **state, char *key, char *value)
{
	t_env	*tmp;
	int		check;

	check = 1;
	tmp = (*state)->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0
			&& ft_strcmp(tmp->value, value) == 0)
			check = 0;
		tmp = tmp->next;
	}
	return (check);
}

static int	ft_del_if(t_state **state, t_cluster *cluster, int i, int j)
{
	t_cluster	*tmp;
	char		*value;
	char		*key;

	tmp = cluster;
	if (ft_strchr(tmp->cmd[i], '=') != NULL)
	{
		key = ft_substr(tmp->cmd[i], 0, j);
		value = ft_substr(tmp->cmd[i], j + 1,
				ft_strlen(tmp->cmd[i]) - j - 1);
		if (ft_value_check(state, key, value) == 1)
		{
			ft_key_error(tmp->cmd[i], "unset", *state);
			free(key);
			free(value);
			return (1);
		}
		free(key);
		free(value);
	}
	return (0);
}

void	ft_del_env(t_state **state, t_cluster *cluster)
{
	t_cluster	*tmp;
	int			i;
	int			j;

	i = 1;
	tmp = cluster;
	while (tmp->cmd[i])
	{
		j = 0;
		while (tmp->cmd[i][j] && tmp->cmd[i][j] != '=')
		{
			if (ft_key_check(tmp->cmd[i][j], j) == 0)
				return (ft_key_error(tmp->cmd[i], "unset", *state));
			j++;
		}
		if (ft_del_if(state, cluster, i, j) == 0)
		{
			ft_del_node(&(*state)->env, tmp->cmd[i]);
			ft_del_node(&(*state)->exp, tmp->cmd[i]);
			(*state)->error = 0;
		}
		i++;
	}
}
