#include "../includes/minishell.h"

static int	ft_setup_clean_argv(t_state *state, char **get_env)
{
	state->pars->clean_argv = ft_put_tilde(get_env, state, state->pars);
	ft_free_double_str(get_env);
	if (!state->pars->clean_argv)
		return (0);
	return (1);
}

static int	ft_setup_thrd_argv(t_state *state)
{
	state->cmd_count = ft_double_str_len(state->pars->clean_argv);
	state->clean_thrd_argv = ft_parser_to_lexer(state->pars->clean_argv,
			state->pars);
	ft_free_double_str(state->pars->clean_argv);
	if (!state->clean_thrd_argv)
		return (0);
	return (1);
}

static void	ft_execute_commands(t_state *state)
{
	ft_cluster(state);
	ft_free_thrd_str(state->clean_thrd_argv);
	ft_executer(state, 0);
}

char	***ft_parser_to_lexer(char **str, t_parser *parser)
{
	int		i;
	int		j;
	char	***dest;

	i = -1;
	dest = malloc(sizeof(char **) * (ft_double_str_len(str) + 1));
	if (!dest)
		return (NULL);
	while (str[++i])
		dest[i] = ft_pipe_split(str[i], ' ', parser);
	dest[i] = NULL;
	i = -1;
	while (dest[++i])
	{
		j = -1;
		while (dest[i][++j])
			dest[i][j] = ft_clean_first_last_quote(dest[i][j]);
	}
	return (dest);
}

void	ft_parser_handler(t_state *state, char **get_env, char **pars_redirect)
{
	ft_free_double_str(pars_redirect);
	if (!ft_setup_clean_argv(state, get_env))
		return ;
	if (!ft_setup_thrd_argv(state))
		return ;
	ft_execute_commands(state);
}
