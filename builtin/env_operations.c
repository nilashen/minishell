#include "../includes/minishell.h"

void	ft_print_env(t_state *state, t_cluster *cluster)
{
	t_env	*tmp;
	int		fd;

	fd = cluster->files->fd_output;
	tmp = state->env;
	while (tmp)
	{
		write(fd, tmp->key, ft_strlen(tmp->key));
		write(fd, "=", 1);
		write(fd, tmp->value, ft_strlen(tmp->value));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	state->error = 0;
}

int	ft_key_check(char arg, int index)
{
	if (index == 0 && ft_isdigit(arg) == 1)
		return (0);
	if (ft_isalnum(arg) != 1 && arg != '_')
		return (0);
	return (1);
}

void	ft_del_node(t_env **list, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp != NULL && ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	if (tmp == *list)
		*list = tmp->next;
	if (prev != NULL)
		prev->next = tmp->next;
	if (tmp->key)
		free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

void	ft_add_env(t_state **state, char *arg)
{
	t_env		*tmp_env;
	int			i;

	i = 0;
	tmp_env = (*state)->env;
	ft_del_node(&tmp_env, arg);
	while (arg[i] && arg[i] != '=' )
	{
		if (ft_key_check(arg[i], i) == 0)
		{
			(*state)->error = 1; 
			return ;
		}
		i++;
	}
	ft_env_addback(&tmp_env, new_env(ft_substr(arg, 0, i),
			ft_substr(arg, i + 1, ft_strlen(arg) - i - 1)));
	(*state)->env = tmp_env;
	(*state)->error = 0;
}

void	ft_export_status(t_state **state, t_cluster *cluster)
{
	int			i;
	int			has_error;

	i = 1;
	has_error = 0;
	if (cluster->cmd[i] == NULL)
		return (ft_print_exp(state, cluster));
	(*state)->error = 0;
	while (cluster->cmd[i])
    {
        ft_add_exp(state, cluster->cmd[i]);
		if ((*state)->error != 0)
		{
			has_error = 1;
			i++;
			continue;
		}
		if (ft_strchr(cluster->cmd[i], '=') != NULL)
			ft_add_env(state, cluster->cmd[i]);
		
		if ((*state)->error != 0)
			has_error = 1;
		i++;
	}
	(*state)->error = has_error;
}
