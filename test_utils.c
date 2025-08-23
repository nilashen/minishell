/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:06:03 by nashena           #+#    #+#             */
/*   Updated: 2025/08/22 12:22:43 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_test_args(char *cmd, const char *arg1, const char *arg2)
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
	argv[0] = ft_strdup(cmd);
	if (arg1)
		argv[1] = ft_strdup(arg1);
	if (arg2)
		argv[2] = ft_strdup(arg2);
	argv[count] = NULL;
	return (argv);
}

char	**create_test_args_multiple(char *cmd, char **args, int arg_count)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (arg_count + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd);
	i = 0;
	while (i < arg_count)
	{
		argv[i + 1] = ft_strdup(args[i]);
		if (!argv[i + 1])
		{
			while (i-- > 0)
				free(argv[i + 1]);
			free(argv[0]);
			free(argv);
			return (NULL);
		}
		i++;
	}
	argv[arg_count + 1] = NULL;
	return (argv);
}

char	**copy_environment(char **envp)
{
	char	**new_envp;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

void	free_environment(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
void	free_test_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	print_test_header(const char *test_name)
{
	ft_printf("\n" GREEN "=== Testing %s ===" RESET "\n", test_name);
}

void	print_test_result(const char *test_case, int result)
{
	if (result == 0)
		ft_printf(GREEN "✓ %s: SUCCESS" RESET "\n", test_case);
	else
		ft_printf(RED "✗ %s: FAILED (exit code: %d)" RESET "\n", test_case,
			result);
}

void	interactive_test_mode(char **envp)
{
	char *line;
	char **test_envp;
	int i;

	ft_printf(GREEN "\n=== Interactive Test Mode ===" RESET "\n");
	ft_printf("Type commands to test (type 'quit' to exit):\n");
	ft_printf("Available: pwd, env, echo <args>, cd <path>, export <args>,unset <args>\n\n");

	test_envp = copy_environment(envp);

	while ((line = readline("test> ")) != NULL)
	{
		if (ft_strlen(line) > 0)
			add_history(line);

		if (ft_strcmp(line, "quit") == 0)
		{
			free(line);
			break ;
		}

		char **tokens = ft_split(line, ' ');
		if (tokens && tokens[0])
		{
			if (ft_strcmp(tokens[0], "pwd") == 0)
				mysh_pwd();
			else if (ft_strcmp(tokens[0], "env") == 0)
				mysh_env(test_envp);
			else if (ft_strcmp(tokens[0], "echo") == 0)
				mysh_echo(tokens);
			else if (ft_strcmp(tokens[0], "cd") == 0)
				mysh_cd(tokens, &test_envp);
			else if (ft_strcmp(tokens[0], "export") == 0)
				mysh_export(tokens, &test_envp);
			else if (ft_strcmp(tokens[0], "unset") == 0)
				mysh_unset(tokens, &test_envp);
			else
				ft_printf("Unknown command: %s\n", tokens[0]);
		}
		if (tokens)
		{
			i = 0;
			while (tokens[i])
				free(tokens[i++]);
			free(tokens);
		}
		free(line);
	}
	free_environment(test_envp);
}