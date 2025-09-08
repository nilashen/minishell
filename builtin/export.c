#include "../includes/minishell.h"

static void	ft_swap_env_nodes(t_env **ptr1, int *swapped)
{
	char	*temp;
	char	*tmpvalue;

	temp = (*ptr1)->key;
	tmpvalue = (*ptr1)->value;
	(*ptr1)->key = (*ptr1)->next->key;
	(*ptr1)->value = (*ptr1)->next->value;
	(*ptr1)->next->key = temp;
	(*ptr1)->next->value = tmpvalue;
	*swapped = 0;
}

void	ft_sort_env_list(t_env *exp, int (*cmp)(char *, char *))
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	swapped = 0;
	lptr = NULL;
	if (exp == NULL)
		return ;
	while (!swapped)
	{
		swapped = 1;
		ptr1 = exp;
		while (ptr1->next != lptr)
		{
			if ((*cmp)(ptr1->key, ptr1->next->key) > 0)
			{
				ft_swap_env_nodes(&ptr1, &swapped);
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	ft_print_exp(t_state **state, t_cluster *cluster)
{
	t_env	*tmp;
	int		fd;

	fd = cluster->files->fd_output;
	tmp = (*state)->exp;
	while (tmp)
	{
		if (tmp->value == NULL)
		{
			write(fd, "declare -x ", ft_strlen("declare -x "));
			write(fd, tmp->key, ft_strlen(tmp->key));
			write(fd, "=\"", 3);
			write(fd, "\"\n", 3);
		}
		else
		{
			write(fd, "declare -x ", ft_strlen("declare -x "));
			write(fd, tmp->key, ft_strlen(tmp->key));
			write(fd, "=\"", 3);
			write(fd, tmp->value, ft_strlen(tmp->value));
			write(fd, "\"\n", 3);
		}
		tmp = tmp->next;
	}
	(*state)->error = 0;
}

void	ft_add_exp(t_state **state, char *arg)
{
	t_env		*tmp_exp;
	int			i;

	i = 0;
	tmp_exp = (*state)->exp;
	ft_del_node(&tmp_exp, arg);
	if (ft_key_check(arg[0], 0) == 0)
		return (ft_key_error(arg, "export", *state));
	while (arg[i] && arg[i] != '=' )
	{
		if (ft_key_check(arg[i], i) == 0)
		{
			ft_key_error(arg, "export", *state);
			return ;
		}
		i++;
	}
	if (ft_strchr(arg, '=') != NULL)
		env_addback(&tmp_exp, new_env(ft_substr(arg, 0, i),
				ft_substr(arg, i + 1, ft_strlen(arg) - i - 1)));
	else
		env_addback(&tmp_exp, new_env(ft_substr(arg, 0, i), NULL));
	ft_sort_env_list(tmp_exp, ft_strcmp);
	(*state)->exp = tmp_exp;
	(*state)->error = 0;
}
