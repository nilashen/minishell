#include "../includes/minishell.h"

int	ft_error_mesage(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	ft_clean_env(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	if (!env || !*env)
		return ;
	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp;
		if (tmp2->key)
			free(tmp2->key);
		if (tmp2->value)
			free(tmp2->value);
		tmp = tmp->next;
		free(tmp2);
	}
	*env = NULL;
}

static void	ft_cleanup_state_memory(t_state *state)
{
	if (state->line)
	{
		ft_all_cluster_free(state);
		free(state->line);
		state->line = NULL;
	}
	if (state->fd != NULL)
		ft_int_free(state);
	if (state->sep_path)
	{
		ft_free_double_str(state->sep_path);
		state->sep_path = NULL;
	}
}

int	ft_full_free(t_state *state, int status)
{
	if (!state)
		exit(status);
	ft_clean_env(&state->env);
	ft_clean_env(&state->exp);
	ft_cleanup_state_memory(state);
	if (state->pars)
	{
		free(state->pars);
		state->pars = NULL;
	}
	free(state);
	if (status != 255 && status != 1)
		ft_putstr_fd("exit\n", 2);
	exit(status);
}

int	ft_exit(char *line, char *msg, t_state *state)
{
	state->error = 2;
	free(line);
	ft_error_mesage(msg);
	return (0);
}
