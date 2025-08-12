/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:02:09 by nashena           #+#    #+#             */
/*   Updated: 2025/08/12 16:25:53 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/* PROJECT INCLUDES */
# include "library/libutils.h"
/* STANDARD LIBRARIES */
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
/* DEFINES */
typedef enum e_token_type
{
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

/* DATA STRUCTURES */

typedef struct s_redir
{
	int				type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char			**envp;
	int				last_exit_status;
	t_cmd			*cmds;
}					t_shell;

/* FUNCTION PROTOTYPES */
int					mysh_echo(char **argv);
int					mysh_cd(char **argv, char ***envp);
int					mysh_pwd(void);
int					mysh_env(char **envp);
int					mysh_exit(char **argv);
int					main(int argc, char **argv, char **envp);
int					mysh_export(char **args, char ***envp);
int					env_count(char **envp);
int					env_set(char ***envp, char *key, char *value);
int					mysh_unset(char **argv, char ***envp);
int					env_unset(char ***envp, char *key);
int					commands_execution(t_shell *shell);
int					execute_single_cmd(t_shell *shell, t_cmd *cmd);
int					is_mysh(char *cmd);
int					execute_mysh(t_shell *shell, t_cmd *cmd);
int					setup_redirections(t_cmd *cmd);
char				*find_executable_path(char *cmd, char **envp);
int					execute_pipeline(t_shell *shell);
void				handle_getcwd_error(void);
void				handle_chdir_error(const char *arg);
int					process_cd_command(char **args, int arg_count, char ***envp);
int 				get_arg_count(char **args);
#endif