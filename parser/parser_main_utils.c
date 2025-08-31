#include "../includes/minishell.h"

static char	*ft_prepare_line(t_state *state)
{
	char	*line;

	if (ft_wait_for_input(state) == 2)
		return (NULL);
	if (!ft_wait_for_input(state))
		return (NULL);
	line = ft_strtrim(state->line, " ");
	return (line);
}

int	ft_parser(t_state *state)
{
	char	*line;

	line = ft_prepare_line(state);
	if (!line)
	{
		if (ft_wait_for_input(state) == 2)
			return (1);
		return (0);
	}
	if (ft_handle_syntax_errors(line, state))
		return (0);
	return (ft_process_parsing(line, state));
}
