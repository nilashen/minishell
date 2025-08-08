/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:14:43 by nashena           #+#    #+#             */
/*   Updated: 2025/08/08 16:39:26 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_mysh(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_mysh(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (mysh_echo(cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (mysh_cd(cmd->args));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (mysh_pwd());
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (mysh_export(cmd->args, &shell->envp));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (mysh_unset(cmd->args, &shell->envp));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (mysh_env(shell->envp));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (mysh_exit(cmd->args));
	return (1);
}
int	commands_execution(t_shell *shell)
{
	t_cmd	*current;
	int		cmd_count;

	if (!shell || !shell->cmds)
		return (1);
	current = shell->cmds;
	cmd_count = 0;
	while (current)
	{
		cmd_count++;
		current = current->next;
	}
	if (cmd_count == 1)
		return (execute_single_cmd(shell, shell->cmds));
	else
		return (execute_pipeline(shell));
}
int	execute_single_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (setup_redirections(cmd) != 0)
		return (1);
	if (is_mysh(cmd->args[0]))
		return (execute_mysh(shell, cmd));
	path = find_executable_path(cmd->args[0], shell->envp);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd->args, shell->envp);
		perror("execve");
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	free(path);
	return (1);
}
int	execute_pipeline(t_shell *shell)
{
	t_cmd	*current;
	int		pipe_fds[2];
	int		prev_fd;
	pid_t	pid;
	int		status;
	int		last_status;

	current = shell->cmds;
	prev_fd = -1;
	last_status = 0;
	while (current)
	{
		if (current->next && pipe(pipe_fds) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (current->next)
			{
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			if (current->next)
				close(pipe_fds[0]);
			if (setup_redirections(current) != 0)
				exit(1);
			if (is_mysh(current->args[0]))
				exit(execute_mysh(shell, current));
			else
			{
				char *path = find_executable_path(current->args[0], shell->envp);
				if (!path)
				{
					ft_printf("minishell: %s: command not found\n", current->args[0]);
					exit(127);
				}
				execve(path, current->args, shell->envp);
				perror("execve");
				exit(126);
			}
		}
		else if (pid > 0)
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (current->next)
			{
				close(pipe_fds[1]);
				prev_fd = pipe_fds[0];
			}
			if (!current->next)
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					last_status = WEXITSTATUS(status);
			}
		}
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
	return (last_status);
}