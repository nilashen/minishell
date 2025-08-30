#include "../includes/minishell.h"

static void	ft_transaction(t_env **ptr1, int *swapped)
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

void	bubble_sort(t_env *exp, int (*cmp)(char *, char *))
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
				ft_transaction(&ptr1, &swapped);
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	ft_print_exp(t_state **state, t_cluster *cluster)
{
	ft_print_export_vars(state, cluster);
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
	bubble_sort(tmp_exp, ft_strcmp);
	(*state)->exp = tmp_exp;
	(*state)->error = 0;
}
