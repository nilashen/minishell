#include "minishell.h"

/**
 * Check if a command is a built-in
 */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (1);
	if (strcmp(cmd, "unset") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	
	return (0);
}

/**
 * Execute a built-in command
 */
int	execute_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);

	if (strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	if (strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd));
	if (strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd(cmd));
	if (strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd));
	if (strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd));
	if (strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(cmd));
	if (strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd));

	return (1);
}

/**
 * Built-in: echo [-n] [string ...]
 * Print arguments separated by spaces, followed by newline (unless -n)
 */
int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;

	// Check for -n option
	if (cmd->argc > 1 && strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}

	// Print arguments
	while (i < cmd->argc)
	{
		printf("%s", cmd->args[i]);
		if (i < cmd->argc - 1)
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return (0);
}

/**
 * Built-in: cd [directory]
 * Change current working directory
 */
int	builtin_cd(t_cmd *cmd)
{
	char	*path;
	char	*home;

	if (cmd->argc > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}

	if (cmd->argc == 1)
	{
		// No argument - go to HOME
		home = getenv("HOME");
		if (!home)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else
	{
		path = cmd->args[1];
	}

	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}

	return (0);
}

/**
 * Built-in: pwd
 * Print current working directory
 */
int	builtin_pwd(t_cmd *cmd)
{
	char	cwd[MAX_PATH];

	(void)cmd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}

/**
 * Built-in: env
 * Print environment variables
 */
int	builtin_env(t_cmd *cmd)
{
	int	i;

	(void)cmd;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}

/**
 * Built-in: export [name=value ...]
 * Set environment variables (simplified version - no options)
 */
int	builtin_export(t_cmd *cmd)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_sign;

	if (cmd->argc == 1)
	{
		// No arguments - just print env like 'env' for now
		return (builtin_env(cmd));
	}

	i = 1;
	while (i < cmd->argc)
	{
		equal_sign = strchr(cmd->args[i], '=');
		if (!equal_sign)
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
			return (1);
		}

		// Split name and value
		*equal_sign = '\0';
		name = cmd->args[i];
		value = equal_sign + 1;

		if (setenv(name, value, 1) != 0)
		{
			perror("minishell: export");
			*equal_sign = '='; // Restore for cleanup
			return (1);
		}

		*equal_sign = '='; // Restore for cleanup
		i++;
	}

	return (0);
}

/**
 * Built-in: unset [name ...]
 * Remove environment variables
 */
int	builtin_unset(t_cmd *cmd)
{
	int	i;

	if (cmd->argc == 1)
		return (0); // No arguments - do nothing

	i = 1;
	while (i < cmd->argc)
	{
		if (unsetenv(cmd->args[i]) != 0)
		{
			perror("minishell: unset");
			return (1);
		}
		i++;
	}

	return (0);
}

/**
 * Built-in: exit [status]
 * Exit the shell with optional status code
 */
int	builtin_exit(t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;

	if (cmd->argc > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}

	if (cmd->argc == 2)
	{
		exit_code = atoi(cmd->args[1]);
	}

	printf("exit\n");
	rl_clear_history();
	exit(exit_code);
}