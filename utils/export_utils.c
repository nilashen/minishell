#include "../includes/minishell.h"

int	ft_validate_key(char *arg, t_state *state)
{
	int	i;

	if (ft_key_check(arg[0], 0) == 0)
	{
		ft_key_error(arg, "export", state);
		state->error = 1;
		return (0);
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_key_check(arg[i], i) == 0)
		{
			ft_key_error(arg, "export", state);
			state->error = 1;
			return (0);
		}
		i++;
	}
	return (i);
}

void	ft_update_pwd_env(t_state **state, char *old_pwd)
{
	char	*oldpwd_entry;

	oldpwd_entry = ft_strjoin("OLDPWD=", old_pwd);
	if (oldpwd_entry)
	{
		ft_add_exp(state, oldpwd_entry);
		ft_add_env(state, oldpwd_entry);
		free(oldpwd_entry);
		(*state)->error = 0;
	}
	else
		(*state)->error = 1;
}
