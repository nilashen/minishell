#include "../includes/minishell.h"

static int	ft_check_last_redirect(t_parser *parser)
{
	int		i;
	char	*trim;

	i = -1;
	while (parser->cleaned[++i])
	{
		trim = ft_strtrim(parser->cleaned[i], " ");
		if (trim[ft_strlen(trim) - 1] == '>'
			|| trim[ft_strlen(trim) - 1] == '<')
		{
			free(trim);
			return (1);
		}
		free(trim);
	}
	return (0);
}

static int	ft_check_sub_redirect(char *line, int start, int i)
{
	char	*sub;

	sub = NULL;
	if (i - start == 0)
		return (0);
	sub = ft_substr(line, start, i - start);
	if (!ft_check_redirect_char(sub, ft_strlen(sub)))
	{
		free(sub);
		return (1);
	}
	free(sub);
	return (0);
}

static int	ft_redher_check(char *line, char typ, char typ2, t_parser *parser)
{
	int		i;
	int		start;

	i = -1;
	while (line[++i])
	{
		if (line[i] == typ && !ft_quote_check(line, i, parser))
		{
			if (line[i +1] == typ)
				++i;
			start = ++i;
			while (line[i] && !ft_quote_check(line, i, parser)
				&& (line[i] == typ || line[i] == typ2 || line[i] == ' '))
				i++;
			if (ft_check_sub_redirect(line, start, i))
				return (1);
		}
	}
	return (0);
}

int	ft_redirection_control(t_parser *parser, int i)
{
	int		check;

	check = -1;
	if (ft_check_last_redirect(parser))
		return (1);
	while (parser->cleaned[++i])
	{
		if (ft_count_real_char(parser->cleaned[i], '>', parser)
			|| ft_count_real_char(parser->cleaned[i], '<', parser))
		{
			check = 0;
			break ;
		}
	}
	i = -1;
	while (parser->cleaned[++i] && check == 0)
		check = ft_redher_check(parser->cleaned[i], '>', '<', parser);
	i = -1;
	while (parser->cleaned[++i] && check == 0)
		check = ft_redher_check(parser->cleaned[i], '<', '>', parser);
	if (check == 0 || check == -1)
		return (0);
	return (1);
}
