/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:02:09 by nashena           #+#    #+#             */
/*   Updated: 2025/08/22 12:16:35 by nashena          ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
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
# ifndef GREEN
#  define GREEN "\033[0;32m"
#  define RED "\033[0;31m"
#  define BLUE "\033[0;34m"
#  define RESET "\033[0m"
# endif
typedef enum e_token_type
{
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}							t_token_type;

/* DATA STRUCTURES */

typedef struct s_redir
{
	int						type;
	char					*file;
	int						fd;
	struct s_redir			*next;
}							t_redir;

typedef struct s_cmd
{
	char					**args;
	t_redir					*redirs;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_shell
{
	char					**envp;
	int						last_exit_status;
	t_cmd					*cmds;
}							t_shell;

typedef struct s_signal
{
	pid_t					pid;
	int						exit_status;
	int						sigint_received;
	int						sigquit_received;
}							t_signal;

extern volatile t_signal	g_sig;
/* FUNCTION PROTOTYPES */
int							mysh_echo(char **argv);
int							mysh_cd(char **argv, char ***envp);
int							mysh_pwd(void);
int							mysh_env(char **envp);
int							mysh_exit(char **argv, t_shell *shell);
int							main(int argc, char **argv, char **envp);
int							mysh_export(char **args, char ***envp);
int							env_count(char **envp);
int							env_set(char ***envp, char *key, char *value);
int							mysh_unset(char **argv, char ***envp);
int							env_unset(char ***envp, char *key);
int							commands_execution(t_shell *shell);
int							execute_single_cmd(t_shell *shell, t_cmd *cmd);
int							is_mysh(char *cmd);
int							execute_mysh(t_shell *shell, t_cmd *cmd);
int							setup_redirections(t_cmd *cmd);
char						*find_executable_path(char *cmd, char **envp);
int							execute_pipeline(t_shell *shell);
void						handle_getcwd_error(void);
void						handle_chdir_error(const char *arg);
int							process_cd_command(char **args, int arg_count,
								char ***envp);
int							get_arg_count(char **args);
int							handle_multiple_args(char **args);
void						handle_single_arg(char *arg);
int							print_exported_vars(char **envp);
int							process_export_arg(char ***envp, char *arg);
void						init_signals(void);
void						cleanup_signals(void);
void						signal_handler_interactive(int sig);
void						signal_handler_child(int sig);
void						setup_interactive_signals(void);
void						setup_child_signals(void);
void						restore_default_signals(void);
void						set_child_pid(pid_t pid);
int							get_exit_status(void);
void						set_exit_status(int status);
int							check_sigint(void);
int							check_sigquit(void);
void						handle_post_execution_signals(void);
// test_functions
void						test_echo(void);
void						test_cd(char **envp);
void						test_export(char **envp);
void						test_unset(char **envp);
void						test_env(char **envp);
void						test_pwd(void);
char						**create_test_args(char *cmd, const char *arg1,
								const char *arg2);
char						**create_test_args_multiple(char *cmd, char **args,
								int arg_count);
char						**copy_environment(char **envp);
void						free_environment(char **envp);
void						free_test_args(char **args);
void						print_test_header(const char *test_name);
void						print_test_result(const char *test_case,
								int result);
void						interactive_test_mode(char **envp);

#endif