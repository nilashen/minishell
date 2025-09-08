#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>

// Macros and project constants
# define IN_CAT 1
# define IN_HEREDOC 2
# define IN_PARENT 3
# define BUFFER_SIZE 42
# define MAX 1024

//  Struct Type Declarations
typedef struct s_files
{
	int		fd_heredoc[4];
	int		error;
	int		fd_input;
	int		fd_output;
	char	*input;
	char	*output;
	char	*heredoc;
}	t_files;

typedef struct s_cluster
{
	char				**cmd;
	pid_t				pid;
	t_files				*files;
	struct s_cluster	*next;
}	t_cluster;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;

typedef struct s_parser
{
	int		i;
	int		j;
	char	**cleaned;
	char	**src;
	char	**clean_argv;
	int		k;
	int		m;
	char	**united_key;
	char	**united_env;
	char	*key;
	int		*ptr_errno;
	t_node	*sublist;
	int		check_redirect;
	int		control;
	int		nr;
	int		r;
	int		check;
	int		count_sq;
	int		count_dq;
	int		check_if;
	int		len_str[2];
	int		len_dollar[2];
	int		d;
	int		dollar_is_first;
}	t_parser;

typedef struct s_lexer
{
	char				*command;
	int					type;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_state
{
	char		***third_arg_clean;
	char		**sep_path;
	char		*line;
	int			cmd_count;
	int			error;
	int			**fd;
	char		**envp;
	t_parser	*pars;
	t_cluster	*cluster;
	t_lexer		**lexer;
	t_env		*env;
	t_env		*exp;
	t_node		*dollar;
}	t_state;

//  Global Variable
extern int	g_sig_status;

//  Environment Management
t_env		*ft_get_env(t_state *state, char **env);
t_env		*new_env(char *key, char *value);
void		ft_env_addback(t_env **lst, t_env *new);
void		ft_add_env(t_state **state, char *arg);
void		ft_del_node(t_env **list, char *key);
void		ft_clean_env(t_env **env);
void		ft_sort_env_list(t_env *exp, int (*cmp)(char *, char *));
void		ft_print_env(t_state *state, t_cluster *cluster);
void		ft_print_exp(t_state **state, t_cluster *cluster);
void		ft_add_exp(t_state **state, char *arg);
void		ft_separate_path(t_state *state);

//  Built-in Commands
void		ft_builtin_echo(t_cluster *cluster, t_state *state);
void		ft_builtin_pwd(t_cluster *cluster, t_state *state);
void		ft_builtin_cd(t_state **state);
void		ft_unset_variable(t_state **state, t_cluster *cluster);
void		ft_export_status(t_state **state, t_cluster *cluster);
void		ft_notdefine_dir(char *s, t_state *state);
void		ft_builtin_cd_error(char *dir, t_state *state);
void		ft_builtin_exit(t_state *state, t_cluster *cluster);
void		ft_dispatch_builtin(t_state *state, t_cluster *tmp);
int			ft_is_builtin_command(t_cluster *cluster);

//  Parsing & Lexer Functions
int			ft_parser(t_state *state);
int			ft_wait_for_input(t_state *state);
void		ft_parser_handler(t_state *state, char **get_env,
				char **pars_redirect);
int			ft_validate_key(char *arg, t_state *state);
int			ft_key_check(char arg, int index);
int			ft_validate_parser_input(t_state *state);
int			ft_validate_syntax(char *line, t_state *state);
int			ft_split_and_clean(char *line, t_state *state, char ***split_str);
int			ft_process_parsed_data(char *line, t_state *state);
int			ft_count_real_char(char *line, char c, t_parser *parser);
int			ft_quote_check(char *str, int len, t_parser *pars);
int			ft_count_quote(char *str, int len, char quote_type);
void		ft_send_cleaner(t_parser *parser);
void		ft_init_paremeter(t_parser *pars);
void		ft_cleanup_arrays(t_parser *pars, int last_index);
int			ft_init_arrays(t_parser *pars, int len);
int			ft_split_key_by_quotes(t_parser *prs, int len);
void		ft_handle_double_quote_check(int **chk_dq, char **tmp,
				t_parser *prs, int len);
char		*ft_prepare_input_line(t_state *state);

//  Redirection & Pipe Checking
int			ft_redirection_control(t_parser *parser, int i);
int			ft_pipe_check(char *line, t_parser *parser);
int			ft_exit_redirect(char *line, char *msg, t_state *state);
void		ft_left_redirect(char *str, int len, char type, t_parser *pars);

//  Environment Variable Handling
int			ft_count_dollar(char *str, t_parser *parser);
int			ft_is_dollar(char *str, int index, t_parser *pars);
char		*ft_dollar_handler(char *str, t_node *dollar, t_parser *prs,
				t_env *env);
char		*ft_united_dollar(t_parser *parser, t_env *env);
char		*ft_dup_key(char *key, t_parser *pars, t_env *env);
char		*ft_join_key(char *key, int index, t_env *env);
char		*ft_refind_env(t_parser *parser, t_env *env);
int			ft_check_is_in(char *str, int index, t_parser *parser);
int			ft_check_special(char *str, int i);
int			ft_check_after_key(char *key);

//  Node and List Handling
t_node		*ft_finish_redirect(char *str, int i, t_parser *pars);
t_node		*ft_new_node(char *content);
void		ft_node_add_back(t_node **lst, t_node *new_node);
char		**ft_node_to_double(t_node **list, int i, int list_size);
int			ft_listlen(t_node *lst);

//  String & Array Utilities
int			ft_strcmp(char *s1, char *s2);
int			ft_double_str_len(char **str);
char		**ft_pipe_split(char *line, char c, t_parser *parser);
char		*ft_new_strjoin(char *s1, char *s2);
char		*ft_resizer(char **str);
char		*ft_node_resizer(t_node *dollar);
int			ft_clean_str(char **str, t_parser *pars);
void		ft_key_error(char *s, char *cmd, t_state *state);
void		ft_free_double_str(char **str);
void		ft_free_third_str(char ***str);
void		ft_free_substr(char **sub, char **sub2, char **sub3,
				t_parser *pars);
char		*ft_cut_dquote(char *str, int len, t_parser *pars);
char		*ft_cut_squote(char *str, int len, t_parser *pars);
char		*ft_clean_first_last_quote(char *str);
char		**ft_put_env(char **str, t_state *state);
char		**ft_redirect_parser(t_parser *pars, t_node *list);
char		**ft_put_tilde(char **str, t_state *state, t_parser *parser);

//  Execution & Process Control
void		ft_execute_pipeline(t_state *state, int i);
void		ft_execute_pipeline_error(char **cmd, char *s, int exit_code);
void		ft_wait(t_state *state, int check);
void		ft_close_pipe(t_state *state, int check);
void		ft_dup_init(t_state *state, t_cluster *cluster, int i, int check);
void		ft_cluster(t_state *state);
char		**ft_fill_cmd(char **arg);
void		ft_cluster_free(t_cluster *cluster);
void		ft_all_cluster_free(t_state *state);
void		ft_int_free(t_state *state);
void		ft_tilda_handler(t_state *state);
t_files		*ft_new_files_node(char **arg, int i);
int			ft_open_input(char *file);
int			ft_open_output(char *file);
int			ft_open_append(char *file);
t_cluster	*ft_file_open_error(t_cluster *cluster, char *file);
void		ft_heredoc_check(t_files *node, char **arg);
char		**ft_find_cmd(char **arg, int len);

//  Miscellaneous and Signals
char		*get_next_line(int fd);
void		ft_update_pwd_env(t_state **state, char *old_pwd);
int			ft_exit(char *line, char *msg, t_state *state);
int			ft_full_free(t_state *state, int status);
void		ft_init_signals(void);
int			ft_get_exit_code(int status);
void		ft_check_control(t_parser *parser);
int			ft_check_redirect_char(char *str, int len);
int			ft_check_full_char(char *str, char c, int len);
void		ft_print_exp(t_state **state, t_cluster *cluster);
int			ft_error_message(char *str);
int			ft_count_quote(char *str, int len, char quote_type);
int			ft_allocate_united_env(t_parser *prs, int count);
int			ft_try_path_command(t_state *state, t_cluster *cluster, int i);
void		ft_pars_str(char *s, t_parser *prs);
void		ft_pars_str_helper(char *s, t_parser *prs);
#endif