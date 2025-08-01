/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:18:40 by nashena           #+#    #+#             */
/*   Updated: 2025/08/01 17:00:54 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_test_args(char *cmd, const char *arg1, const char *arg2)
{
	char	**argv;
	int		count;

	count = 1;
	if (arg1)
		count++;
	if (arg2)
		count++;
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	argv[0] = cmd;
	if (arg1)
		argv[1] = (char *)arg1;
	if (arg2)
		argv[2] = (char *)arg2;
	argv[count] = NULL;
	return (argv);
}


int	main(int argc, char **argv, char **envp)
{
	char	**test_args;
	int		result;
	const char *arg1;
	const char *arg2;

	if (argc < 2)
	{
		ft_printf("Usage: %s <command> [args...]\n", argv[0]);
		ft_printf("Available commands: pwd, echo, env, cd, exit\n");
		return (1);
	}
	if (ft_strcmp(argv[1], "pwd") == 0)
		return (mysh_pwd());
	else if (ft_strcmp(argv[1], "env") == 0)
		return (mysh_env(envp));
	else if (ft_strcmp(argv[1], "echo") == 0)
	{
		arg1 = NULL;
		arg2 = NULL;
		if (argc > 2)
			arg1 = argv[2];
		if (argc > 3)
			arg2 = argv[3];

		test_args = create_test_args("echo", arg1, arg2);
		if (test_args)
		{
			mysh_echo(test_args);
			free(test_args);
		}
		return (0);
	}
	else if (ft_strcmp(argv[1], "cd") == 0)
	{
		arg1 = NULL;
		arg2 = NULL; 
		if (argc > 2)
			arg1 = argv[2];
		test_args = create_test_args("cd", arg1, NULL);
		result = mysh_cd(test_args);
		free(test_args);
		return (result);
	}
	else if (ft_strcmp(argv[1], "exit") == 0)
	{
		arg1 = NULL;
		arg2 = NULL;
		if (argc > 2)
			arg1 = argv[2];

		test_args = create_test_args("exit", arg1, NULL);
		mysh_exit(test_args);
	}
	else
	{
		ft_printf("Unknown command: %s\n", argv[1]);
		return (1);
	}
	return (0);
}