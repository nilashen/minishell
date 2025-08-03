/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:02:09 by nashena           #+#    #+#             */
/*   Updated: 2025/08/03 17:13:11 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/* PROJECT INCLUDES */
# include "library/libutils.h"
/* STANDARD LIBRARIES */
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

/* DATA STRUCTURES */
typedef struct s_cmd
{
	char				**args;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_shell
{
	char				**envp;
	int					last_exit_status;
	t_cmd				*cmds;
}	t_shell;

/* FUNCTION PROTOTYPES */
int		mysh_echo(char **argv);
int		mysh_pwd(void);
int		mysh_cd(char **argv);
int		mysh_env(char **envp);
int		mysh_exit(char **argv);
int		main(int argc, char **argv, char **envp);
int		mysh_export(char **args, char ***envp);
int		env_count(char **envp);
int		env_set(char ***envp, char *key, char *value);
int		mysh_unset(char **argv, char ***envp);
int		env_unset(char ***envp, char *key);
int		commands_execution(t_shell *shell);
int		execute_single_cmd(t_shell *shell, t_cmd *cmd);
int		is_mysh(char *cmd);
int		execute_mysh(t_shell *shell, t_cmd *cmd);
#endif