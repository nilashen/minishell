#include "../includes/minishell.h"

static void	ft_write_declare_header(int fd, char *key)
{
	write(fd, "declare -x ", 11);
	write(fd, key, ft_strlen(key));
}

static void	ft_print_var_with_value(int fd, char *key, char *value)
{
	ft_write_declare_header(fd, key);
	write(fd, "=\"", 2);
	write(fd, value, ft_strlen(value));
	write(fd, "\"\n", 2);
}

static void	ft_print_var_without_value(int fd, char *key)
{
	ft_write_declare_header(fd, key);
	write(fd, "\n", 1);
}

void	ft_print_export_vars(t_state **state, t_cluster *cluster)
{
	t_env	*tmp;
	int		fd;

	fd = cluster->files->fd_output;
	tmp = (*state)->exp;
	while (tmp)
	{
		if (tmp->value == NULL)
			ft_print_var_without_value(fd, tmp->key);
		else
			ft_print_var_with_value(fd, tmp->key, tmp->value);
		tmp = tmp->next;
	}
	(*state)->error = 0;
}

void	ft_print_exp_wrapper(t_state **state, t_cluster *cluster)
{
	ft_print_export_vars(state, cluster);
}
