#include "../includes/minishell.h"

static int	ft_clean_str(char **str, t_parser *pars)
{
	int	i;
	int	len;

	i = -1;
	len = ft_double_str_len(str);
	pars->src = malloc(sizeof(char *) * (len + 1));
	pars->cleaned = malloc(sizeof(char *) * (len + 1));
	if (!pars->src || !pars->cleaned || !str)
		return (0);
	while (str[++i])
	{
		pars->src[i] = ft_strtrim(str[i], " ");
		pars->cleaned[i] = malloc(sizeof(char) * ft_strlen(pars->src[i]) + 1);
		if (!pars->cleaned[i])
			return (0);
	}
	pars->src[i] = NULL;
	pars->cleaned[i] = NULL;
	ft_send_cleaner(pars);
	ft_free_double_str(str);
	ft_free_double_str(pars->src);
	return (1);
}

static char	***ft_parser_to_lexer(char **str, t_parser *parser)
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

static char	**ft_put_env(char **str, t_state *state)
{
	t_env	*env;
	char	**dest;
	int		i;
	int		count_dolr;

	env = state->env;
	dest = malloc(sizeof(char *) * (ft_double_str_len(str) + 1));
	if (!dest)
		return (NULL);
	dest[ft_double_str_len(str)] = NULL;
	i = -1;
	while (str[++i])
	{
		count_dolr = ft_count_dollar(str[i], state->pars);
		env = state->env;
		if (count_dolr)
			dest[i] = ft_dolar_handler(str[i], state->dolar, state->pars, env);
		else
			dest[i] = ft_strdup(str[i]);
	}
	return (dest);
}

static void	ft_parser_handler(t_state *state, char **get_env,
	char **pars_redirect)
{
	ft_free_double_str(pars_redirect);
	state->pars->clean_argv = ft_put_tilde(get_env, state, state->pars);
	ft_free_double_str(get_env);
	state->cmd_count = ft_double_str_len(state->pars->clean_argv);
	state->clean_thrd_argv = ft_parser_to_lexer(state->pars->clean_argv,
			state->pars);
	ft_free_double_str(state->pars->clean_argv);
	ft_cluster(state);
	ft_free_thrd_str(state->clean_thrd_argv);
	ft_execute_pipeline(state, 0);
}

int	ft_parser(t_state *state)
{
	char	*line;
	char	**split_str;
	char	**pars_redirect;
	char	**get_env;

	if (ft_wait_for_input(state) == 2)
		return (1);
	if (!ft_wait_for_input(state))
		return (0);
	line = ft_strtrim(state->line, " ");
	if (ft_quote_check(line, (int)ft_strlen(line), state->pars))
		return (ft_exit(line, "Error: Open quotation mark !", state));
	if (ft_pipe_check(line, state->pars))
		return (ft_exit(line, "Error: Failure to use pipe ! ", state));
	split_str = ft_pipe_split(line, '|', state->pars);
	ft_clean_str(split_str, state->pars);
	if (ft_redirection_control(state->pars, -1))
		return (ft_exit_redirect(line, "Error: Redirect syntax error !",
				state));
	free(line);
	pars_redirect = ft_redirect_parser(state->pars, state->dolar);
	ft_free_double_str(state->pars->cleaned);
	get_env = ft_put_env(pars_redirect, state);
	ft_parser_handler(state, get_env, pars_redirect);
	return (0);
}
