#include "minishell.h"

/**
 * Check if command contains a path separator
 */
int	has_path_separator(char *cmd)
{
	return (strchr(cmd, '/') != NULL);
}

/**
 * Find the full path of a command using PATH environment variable
 */
char	*find_command_path(char *cmd)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;
	int		cmd_len;
	int		dir_len;

	// If command already has path separator, return as is
	if (has_path_separator(cmd))
	{
		if (access(cmd, F_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	// Get PATH environment variable
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	cmd_len = strlen(cmd);
	dir = strtok(path_copy, ":");
	
	while (dir)
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + cmd_len + 2); // +2 for '/' and '\0'
		if (full_path)
		{
			strcpy(full_path, dir);
			strcat(full_path, "/");
			strcat(full_path, cmd);
			
			if (access(full_path, F_OK) == 0)
			{
				free(path_copy);
				return (full_path);
			}
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	
	free(path_copy);
	return (NULL);
}

/**
 * Execute a single command
 */
int	execute_command(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);

	// Find the command path
	cmd_path = find_command_path(cmd->args[0]);
	if (!cmd_path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		return (127);
	}

	// Fork and execute
	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (execve(cmd_path, cmd->args, environ) == -1)
		{
			perror("execve failed");
			exit(127);
		}
	}
	else if (pid > 0)
	{
		// Parent process - wait for child
		waitpid(pid, &status, 0);
		free(cmd_path);
		
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	else
	{
		// Fork failed
		perror("fork failed");
		free(cmd_path);
		return (1);
	}
	return (0);
}