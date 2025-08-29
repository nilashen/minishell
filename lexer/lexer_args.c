#include "../includes/minishell.h"

static int	ft_check_redirect(char *arg)
{
	if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0
		|| ft_strcmp(arg, "<<") == 0 || ft_strcmp(arg, ">>") == 0)
		return (1);
	else
		return (0);
}

int	ft_cmd_len(char **arg)
{
	int	i;
	int	len;
	int	rdr;

	i = 0;
	rdr = 0;
	len = 0;
	while (arg[i++])
		len++;
	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0
			|| ft_strcmp(arg[i], ">>") == 0 || ft_strcmp(arg[i], "<<") == 0)
			rdr++;
		i++;
	}
	return (len - (rdr * 2));
}

char	**ft_fill_cmd(char **arg)
{
	int		len;
	char	**cmd;

	len = ft_cmd_len(arg);
	cmd = ft_find_cmd_safe(arg, len);
	if (!cmd)
		return (NULL);
	cmd[len] = NULL;
	return (cmd);
}

char	**ft_find_cmd(char **arg, int len)
{
	return (ft_find_cmd_safe(arg, len));
}

int	ft_check_redirect_public(char *arg)
{
	return (ft_check_redirect(arg));
}