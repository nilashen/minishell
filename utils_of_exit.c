/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:19:06 by nashena           #+#    #+#             */
/*   Updated: 2025/08/13 18:44:59 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_with_invalid_arg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
}

static int	is_valid_number(const char *str, long *result)
{
	int		i;
	long	val;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || (str[i] < '0' || str[i] > '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (0);
	val = ft_atoi(str);
	*result = val;
	return (1);
}

static int	normalize_exit_code(long code)
{
	if (code < 0)
		return (((int)(code % 256) + 256) % 256);
	return (code % 256);
}

int	handle_multiple_args(char **args)
{
	long	exit_code_long;

	if (is_valid_number(args[1], &exit_code_long))
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit_with_invalid_arg(args[1]);
	return (0);
}

void	handle_single_arg(char *arg)
{
	long	exit_code_long;
	int		exit_code;

	if (is_valid_number(arg, &exit_code_long))
	{
		exit_code = normalize_exit_code(exit_code_long);
		exit(exit_code);
	}
	exit_with_invalid_arg(arg);
}
