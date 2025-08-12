/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:11:25 by nashena           #+#    #+#             */
/*   Updated: 2025/08/12 11:48:38 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mysh_echo(char **argv)
{
	int	i;
	int	new_line;

	if (!argv || !argv[0])
		return (1);
	new_line = 1;
	i = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		new_line = 0;
		i = 2;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}
int	mysh_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		handle_getcwd_error();
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	mysh_cd(char **args)
{
	char	*path;
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
int	mysh_env(char **envp)
{
	int	i;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	mysh_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
		exit_code = ft_atoi(args[1]);
	exit(exit_code);
}

int	mysh_export(char **args, char ***envp)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;

	if (!args[1])
		return (mysh_env(*envp));
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = args[i];
			value = equal_sign + 1;
			if (env_set(envp, key, value) != 0)
				return (1);
			*equal_sign = '=';
		}
		else
		{
			if (env_set(envp, args[i], "") != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	mysh_unset(char **argv, char ***envp)
{
	int	i;

	if (!envp || !*envp)
		return (1);
	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		env_unset(envp, argv[i]);
		i++;
	}
	return (0);
}
