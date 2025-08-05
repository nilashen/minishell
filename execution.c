/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:14:43 by nashena           #+#    #+#             */
/*   Updated: 2025/08/05 12:24:21 by nashena          ###   ########.fr       */
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
}