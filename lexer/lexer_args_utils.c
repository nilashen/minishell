#include "../includes/minishell.h"

static char	**ft_allocate_cmd_array(int len)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	cmd[len] = NULL;
	return (cmd);
}

static char	**ft_free_cmd_on_error(char **cmd, int j)
{
	int	k;

	k = 0;
	while (k < j)
		free(cmd[k++]);
	free(cmd);
	return (NULL);
}

static int	ft_process_first_arg_safe(char **arg, char **cmd, int *i, int *j)
{
	if (ft_check_redirect_public(arg[*i]) == 1)
	{
		if (arg[*i + 1] != NULL)
			(*i)++;
		else
			return (0);
	}
	else
	{
		cmd[(*j)++] = ft_strdup(arg[*i]);
		if (!cmd[*j - 1])
			return (0);
	}
	return (1);
}

static int	ft_process_other_args_safe(char **arg, char **cmd, int *i, int *j)
{
	if (ft_check_redirect_public(arg[*i]) == 1)
	{
		if (arg[*i + 1] != NULL)
			(*i)++;
		else
			return (0);
	}
	else if (ft_check_redirect_public(arg[*i - 1]) == 0)
	{
		cmd[(*j)++] = ft_strdup(arg[*i]);
		if (!cmd[*j - 1])
			return (0);
	}
	return (1);
}

char	**ft_find_cmd_safe(char **arg, int len)
{
	int		i;
	char	**cmd;
	int		j;

	cmd = ft_allocate_cmd_array(len);
	if (!cmd)
		return (NULL);
	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (i == 0)
		{
			if (!ft_process_first_arg_safe(arg, cmd, &i, &j))
				return (ft_free_cmd_on_error(cmd, j));
		}
		else
		{
			if (!ft_process_other_args_safe(arg, cmd, &i, &j))
				return (ft_free_cmd_on_error(cmd, j));
		}
	}
	cmd[j] = NULL;
	return (cmd);
}