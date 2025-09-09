/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:26:20 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:26:53 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_validate_parser_input(t_state *state)
{
	if (!state || !state->line || !state->pars)
	{
		if (state)
			state->error = 2;
		return (1);
	}
	if (ft_wait_for_input(state) == 2)
		return (1);
	if (!ft_wait_for_input(state))
		return (0);
	return (-1);
}

char	*ft_prepare_input_line(t_state *state)
{
	char	*line;

	line = ft_strtrim(state->line, " ");
	if (!line)
	{
		state->error = 2;
		return (NULL);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	ft_validate_syntax(char *line, t_state *state)
{
	if (ft_qcheck(line, (int)ft_strlen(line), state->pars))
	{
		ft_putendl_fd("Error: Open quotation mark !", STDERR_FILENO);
		state->error = 258;
		return (1);
	}
	if (ft_pipe_check(line, state->pars))
	{
		ft_putendl_fd("Error: Failure to use pipe !", STDERR_FILENO);
		state->error = 258;
		return (1);
	}
	return (0);
}

int	ft_split_and_clean(char *line, t_state *state, char ***split_str)
{
	*split_str = ft_pipe_split(line, '|', state->pars);
	if (!*split_str)
	{
		free(line);
		state->error = 2;
		return (1);
	}
	if (!ft_clean_str(*split_str, state->pars))
	{
		ft_free_double_str(*split_str);
		free(line);
		state->error = 2;
		return (1);
	}
	return (0);
}

int	ft_process_parsed_data(char *line, t_state *state)
{
	char	**pars_redirect;
	char	**get_env;

	if (ft_redirection_control(state->pars, -1))
		return (ft_exit_redirect(line, "Error: Redirect syntax error !",
				state));
	free(line);
	pars_redirect = ft_redirect_parser(state->pars, state->dollar);
	ft_free_double_str(state->pars->cleaned);
	get_env = ft_put_env(pars_redirect, state);
	ft_parser_handler(state, get_env, pars_redirect);
	return (0);
}
