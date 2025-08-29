#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
#include <termios.h>

# define IN_CAT 1
# define IN_HERADOC 2
# define IN_PARENT 3
# define BUFFER_SIZE 42
# define MAX 1024


typedef struct s_files
{
	int		fd_heredoc[2];
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
	char				*str;
	struct s_node		*next;

}	t_node;
typedef struct s_parser
{
	// clean func parameter
	int		i;
	int		j;
	char	**cleaned;
	char	**src;
	char	**clean_argv;

	//quote check func parameter
	int		k;
	int		m;
	int		check;
	int		count_sq;
	int		count_dq;
	int		check_if;

	//	dolar
	int		len_str[2];
	int		len_dolar[2];
	int		d;
	int		dolar_is_first;
	char	**united_key;
	char	**united_env;
	char	*key;
	int		*ptr_errno;

	//	redirect
	t_node	*sublist;
	int		check_redirect;
	int		control;
	int		nr;
	int		r;
}	t_parser;

typedef struct s_lexer
{
	char				*command;
	int					type;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_state
{
	char		***clean_thrd_argv;
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
	t_node		*dolar;
}	t_state;

//			get env functions
t_env		*get_env(t_state *state, char **env);
void		env_addback(t_env **lst, t_env *new);
void		ft_sep_path(t_state *state);
t_env		*new_env(char *key, char *value);
extern int 	g_sig_status;


//			built in functions
void		env_addback(t_env **lst, t_env *new);
void		ft_add_env(t_state **state, char *arg);
void		ft_echo(t_cluster *cluster, t_state *state);
void		ft_del_env(t_state **state, t_cluster *cluster);
void		ft_pwd(t_cluster *cluster, t_state *state);
void		ft_cd(t_state **state);
void		ft_notdefine_dir(char *s, t_state *state);
void		ft_cd_error(char *dir, t_state *state);
int			ft_strcmp(char *s1, char *s2);
void		bubble_sort(t_env *exp, int (*cmp)(char *, char *));
void		ft_print_exp(t_state **state, t_cluster *cluster);
void		ft_add_exp(t_state **state, char *arg);
void		ft_del_node(t_env **list, char *key);
void		ft_export_status(t_state **state, t_cluster *cluster);
void		ft_key_error(char *s, char *cmd, t_state *state);
int			ft_key_check(char arg, int index);
void		ft_clean_env(t_env **env);

//				parser init functions
int			ft_parser(t_state *state);
char		**ft_pipe_split(char *line, char c, t_parser *parser);
int			ft_count_real_char(char *line, char c, t_parser *parser);
int			ft_wait_for_input(t_state *state);
int			ft_exit(char *line, char *msg, t_state *state);

//				string clean functions
void		ft_send_cleaner(t_parser *parser);
int			ft_error_mesage(char *str);
void		ft_free_double_str(char **str);
int			ft_double_str_len(char **str);
void		ft_free_double_str(char **str);
int			ft_full_free(t_state *state, int status);

//				string control functions
int			ft_redirection_control(t_parser *parser, int i);
int			ft_exit_redirect(char *line, char *msg, t_state *state);
int			ft_pipe_check(char *line, t_parser *parser);

//				quote functions
int			ft_quote_check(char *str, int len, t_parser *pars);
void		ft_init_paremeter(t_parser *pars);
int			ft_count_quote(char *str, int len, char quote_type);
char		*ft_cut_dquote(char *str, int len, t_parser *pars);
char		*ft_cut_squote(char *str, int len, t_parser *pars);

//							Put env functions
int			ft_count_dolar(char *str, t_parser *parser);
int			ft_isdolr(char *str, int index, t_parser *pars);
int			ft_check_is_in(char *str, int index, t_parser *parser);
char		*ft_dolar_handler(char *str, t_node *dolar, t_parser *prs,
				t_env *env);
void		ft_pars_str(char *s, t_parser *prs);
void		ft_pars_str_helper(char *s, t_parser *prs);
char		*ft_united_dolar(t_parser *parser, t_env *env);
int			ft_check_after_key(char *key);
int			ft_check_special(char *str, int i);
char		*ft_dup_key(char *key, t_parser *pars, t_env *env);
char		*ft_join_key(char *key, int index, t_env *env);
char		*ft_resizer(char **str);
char		*ft_refind_env(t_parser *parser, t_env *env);
char		**ft_put_tilde(char **str, t_state *state, t_parser *parser);

//					Redirect parsing functions
void		ft_left_redirect(char *str, int len, char type, t_parser *pars);
int			ft_listlen(t_node *lst);
int			ft_check_redirect_char(char *str, int len);
void		ft_check_control(t_parser *parser);
void		ft_free_substr(char **sub, char **sub2, char **sub3,
				t_parser *pars);

// 				Parser utils functions
t_node		*ft_finish_redirect(char *str, int i, t_parser *pars);
char		**ft_node_to_double(t_node **list, int i, int list_size);
char		**ft_redirect_parser(t_parser *pars, t_node *list);
void		ft_node_add_back(t_node **lst, t_node *new_node);
char		*ft_new_strjoin(char *s1, char *s2);
char		*ft_node_resizer(t_node *dolar);
t_node		*ft_new_node(char *content);

//					3D string functions
char		*ft_clean_first_last_quote(char *str);
void		ft_free_thrd_str(char ***str);
int			ft_check_full_char(char *str, char c, int len);
void		ft_init_signals(void);
void		ft_reset_signals_child(void);
void		disable_quit_echo(void);

//					lexer functions
void		ft_cluster(t_state *state);
int			ft_strcmp(char *s1, char *s2);
char		**ft_fill_cmd(char **arg);
t_files		*ft_new_files_node(char **arg, int i);
int			ft_open_input(char *file);
int			ft_open_output(char *file);
int			ft_open_append(char *file);
t_cluster	*ft_file_open_error(t_cluster *cluster, char *file);
void		ft_print_env(t_state *state, t_cluster *cluster);
void		ft_route(t_state *state, t_cluster *tmp);
int			ft_check_built(t_cluster *cluster);
char		**ft_find_cmd_safe(char **arg, int len);
int			ft_check_redirect_public(char *arg);

//					executer functions 
void		ft_close_pipe(t_state *state, int check);
void		ft_dup_init(t_state *state, t_cluster *cluster, int i, int check);
void		ft_executer_error(char	**cmd, char *s, int exit_code);
void		ft_executer(t_state *state, int i);
void		ft_wait(t_state *state, int check);
void		ft_heredoc_check(t_files *node, char **arg);
char		**ft_find_cmd(char **arg, int len);
char		*get_next_line(int fd);
void		ft_all_cluster_free(t_state *state);
void		ft_built_exit_cmd(t_state *state, t_cluster *cluster);
void		ft_int_free(t_state *state);
void		ft_tilda_handler(t_state *state);
void		ft_cluster_free(t_cluster *cluster);
#endif
