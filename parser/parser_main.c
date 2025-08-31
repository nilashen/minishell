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
		pars->cleaned[i] = malloc(sizeof(char) * (ft_strlen(pars->src[i]) + 1));
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

static char	*ft_process_env_var(char *str, t_state *state)
{
	int		count_dolr;
	t_env	*env;

	count_dolr = ft_count_dolar(str, state->pars);
	env = state->env;
	if (count_dolr)
		return (ft_dolar_handler(str, state->dolar, state->pars, env));
	else
		return (ft_strdup(str));
}

static char	**ft_put_env(char **str, t_state *state)
{
	char	**dest;
	int		i;

	dest = malloc(sizeof(char *) * (ft_double_str_len(str) + 1));
	if (!dest)
		return (NULL);
	dest[ft_double_str_len(str)] = NULL;
	i = -1;
	while (str[++i])
	{
		dest[i] = ft_process_env_var(str[i], state);
		if (!dest[i])
		{
			ft_free_double_str(dest);
			return (NULL);
		}
	}
	return (dest);
}

int	ft_handle_syntax_errors(char *line, t_state *state)
{
	if (ft_quote_check(line, (int)ft_strlen(line), state->pars))
		return (ft_exit(line, "minishell: syntax error: unclosed quotes", state));
	if (ft_pipe_check(line, state->pars))
		return (ft_exit(line, "minishell: syntax error near token `|'", state));
	return (0);
}

int	ft_process_parsing(char *line, t_state *state)
{
	char	**split_str;
	char	**pars_redirect;
	char	**get_env;

	split_str = ft_pipe_split(line, '|', state->pars);
	if (!ft_clean_str(split_str, state->pars))
		return (ft_exit(line, "Error: Memory allocation failed", state));
	if (ft_redirection_control(state->pars, -1))
		return (ft_exit_redirect(line, "minishell: syntax error near token", state));
	free(line);
	pars_redirect = ft_redirect_parser(state->pars, state->dolar);
	ft_free_double_str(state->pars->cleaned);
	get_env = ft_put_env(pars_redirect, state);
	if (get_env)
		ft_parser_handler(state, get_env, pars_redirect);
	else
		ft_free_double_str(pars_redirect);
	return (0);
}
