#include "../includes/minishell.h"

int	ft_count_real_char(char *line, char c, t_parser *parser)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(line) && line[i] != '\0')
	{
		if (line[i] == c && ft_quote_check(line, i, parser) == 0)
			count++;
		else if (line[i] == c && ft_quote_check(line, i, parser) != 0)
		{
			while (line[++i])
			{
				if ((line[i] == c || line[i + 1] == '\0')
					&& ft_quote_check(line, i, parser) == 0)
				{
					count++;
					break ;
				}
			}
		}
		i++;
	}
	return (count);
}

int	ft_wait_for_input(t_state *state)
{
	int	i;

	i = 0;
	if (!state->line)
		return (2);
	while (state->line[i])
	{
		if ((state->line[i] != 10) && (state->line[i] != 32))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_resizer(char **str)
{
	char	*line;
	int		i;

	line = ft_strdup("");
	i = -1;
	while (str[++i])
		line = ft_new_strjoin(line, str[i]);
	ft_free_double_str(str);
	return (line);
}

char	*ft_clean_first_last_quote(char *str)
{
	int		i;
	int		j;
	char	*dest;
	int		dq;
	int		sq;

	i = 0;
	j = -1;
	dq = (str[0] == '"' && str[ft_strlen(str) - 1] == '"');
	sq = (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'');
	if ((dq || sq) && ft_check_redirect_char(str + 1, ft_strlen(str + 1) - 1))
	{
		dest = malloc(sizeof(char) * ft_strlen(str) - 1);
		if (!dest)
			return (NULL);
		while (str[++i] && (i < ((int)ft_strlen(str))))
			dest[++j] = str[i];
		dest[j] = '\0';
		free(str);
		return (dest);
	}
	return (str);
}

int	ft_check_full_char(char *str, char c, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}
