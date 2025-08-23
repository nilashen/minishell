/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:18:40 by nashena           #+#    #+#             */
/*   Updated: 2025/08/22 12:23:46 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		**test_args;
	int			result;
	const char	*arg1;
	const char	*arg2;
	char		**test_envp;
	char		**export_args;

	if (argc == 1)
	{
		ft_printf(BLUE "=== MINISHELL COMPREHENSIVE TEST SUITE ===" RESET "\n");
		test_pwd();
		test_env(envp);
		test_echo();
		test_cd(envp);
		test_export(envp);
		test_unset(envp);
		ft_printf(GREEN "\n=== All Tests Completed ===" RESET "\n");
		ft_printf("Run with 'interactive' for interactive testing mode\n");
		return (0);
	}
	if (argc == 2 && ft_strcmp(argv[1], "interactive") == 0)
	{
		interactive_test_mode(envp);
		return (0);
	}
	if (argc < 2)
	{
		ft_printf("Usage: %s <command> [args...]\n", argv[0]);
		ft_printf("       %s interactive\n", argv[0]);
		ft_printf("       %s (no args for full test suite)\n", argv[0]);
		ft_printf("Available commands: pwd, echo, env, cd, exit, export, unset\n");
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
			result = mysh_echo(test_args);
			free(test_args);
			return (result);
		}
		return (1);
	}
	else if (ft_strcmp(argv[1], "cd") == 0)
	{
		test_envp = copy_environment(envp);
		arg1 = NULL;
		if (argc > 2)
			arg1 = argv[2];
		test_args = create_test_args("cd", arg1, NULL);
		result = mysh_cd(test_args, &test_envp);
		free(test_args);
		free_environment(test_envp);
		return (result);
	}
	else if (ft_strcmp(argv[1], "export") == 0)
	{
		test_envp = copy_environment(envp);
		export_args = malloc(sizeof(char *) * argc);
		export_args[0] = "export";
		for (int i = 2; i < argc; i++)
			export_args[i - 1] = argv[i];
		export_args[argc - 1] = NULL;
		result = mysh_export(export_args, &test_envp);
		free(export_args);
		free_environment(test_envp);
		return (result);
	}
	else if (ft_strcmp(argv[1], "unset") == 0)
	{
		test_envp = copy_environment(envp);
		arg1 = NULL;
		if (argc > 2)
			arg1 = argv[2];
		test_args = create_test_args("unset", arg1, NULL);
		result = mysh_unset(test_args, &test_envp);
		free(test_args);
		free_environment(test_envp);
		return (result);
	}
	else if (ft_strcmp(argv[1], "exit") == 0)
	{
		arg1 = NULL;
		if (argc > 2)
			arg1 = argv[2];
		test_args = create_test_args("exit", arg1, NULL);
		mysh_exit(test_args, NULL);
	}
	else
	{
		ft_printf("Unknown command: %s\n", argv[1]);
		return (1);
	}
	return (0);
}
