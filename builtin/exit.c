#include "../includes/minishell.h"

static int	ft_is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long	ft_safe_atol(char *str, int *overflow)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static void	ft_exit_with_error(t_state *state, char *arg, char *msg, int code)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	ft_full_free(state, code);
	// if (isatty(fileno(stdin)))
	// 	ft_putstr_fd("exit\n", 2);
	
	// ft_putstr_fd("minishell: exit: ", 2);
	// ft_putstr_fd(arg, 2);
	// ft_putstr_fd(msg, 2);
	// ft_full_free(state, code);
}

void	ft_built_exit_cmd(t_state *state, t_cluster *cluster)
{
	long	exit_code;
	int		overflow;

	if (cluster->cmd[1] != NULL)
	{
		if (!ft_is_valid_number(cluster->cmd[1]))
			ft_exit_with_error(state, cluster->cmd[1], 
				": numeric argument required\n", 255);
		overflow = 0;
		exit_code = ft_safe_atol(cluster->cmd[1], &overflow);
		if (overflow)
			ft_exit_with_error(state, cluster->cmd[1], 
				": numeric argument required\n", 255);
		if (cluster->cmd[2] != NULL)
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			state->error = 1;
			return;
		}
		ft_full_free(state, (int)(exit_code % 256));
	}
	ft_full_free(state, 0);
}
