#include "../includes/minishell.h"

int	ft_clean_str(char **str, t_parser *pars)
{
	int	i;
	int	len;

	if (!str || !pars)
		return (0);
	len = ft_double_str_len(str);
	if (!ft_init_arrays(pars, len))
		return (0);
	i = -1;
	while (str[++i])
	{
		pars->src[i] = ft_strtrim(str[i], " ");
		if (!pars->src[i])
			return (ft_cleanup_arrays(pars, i), 0);
		pars->cleaned[i] = malloc(sizeof(char) * (ft_strlen(pars->src[i]) + 1));
		if (!pars->cleaned[i])
			return (free(pars->src[i]), ft_cleanup_arrays(pars, i), 0);
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

char	**ft_put_env(char **str, t_state *state)
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

void	ft_parser_handler(t_state *state, char **get_env,
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
	int		validation_result;
	
	validation_result = ft_validate_parser_input(state);
	if (validation_result != -1)
		return (validation_result);
	line = ft_prepare_input_line(state);
	if (!line)
		return (0);
	if (ft_validate_syntax(line, state))
		return (1);
	if (ft_split_and_clean(line, state, &split_str))
		return (1);
	return (ft_process_parsed_data(line, state));
}
