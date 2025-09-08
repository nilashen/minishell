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

static void	ft_add_export_node(t_env **exp, char *arg, int key_len)
{
	if (ft_strchr(arg, '=') != NULL)
		ft_env_addback(exp, new_env(ft_substr(arg, 0, key_len),
				ft_substr(arg, key_len + 1, ft_strlen(arg) - key_len - 1)));
	else
		ft_env_addback(exp, new_env(ft_substr(arg, 0, key_len), NULL));
	ft_sort_env_list(*exp, ft_strcmp);
}

void	ft_add_exp(t_state **state, char *arg)
{
	t_env	*tmp_exp;
	int		key_len;

	tmp_exp = (*state)->exp;
	ft_del_node(&tmp_exp, arg);
	key_len = ft_validate_key(arg, *state);
	if (key_len == 0)
		return ;
	ft_add_export_node(&tmp_exp, arg, key_len);
	(*state)->exp = tmp_exp;
	(*state)->error = 0;
}

