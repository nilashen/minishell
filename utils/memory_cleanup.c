#include "../includes/minishell.h"

int	ft_error_message(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	ft_clean_env(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp2->key);
		free(tmp2->value);
		tmp = tmp->next;
		free(tmp2);
	}
}

int	ft_full_free(t_state *state, int status)
{
	ft_clean_env(&state->env);
	ft_clean_env(&state->exp);
	ft_free_double_str(state->sep_path);
	if (state->line)
	{
		ft_all_cluster_free(state);
		free(state->line);
	}
	if (state->fd != NULL)
		ft_int_free(state);
	free(state->pars);
	free(state);
	if (status != 255 && status != 1)
		ft_putstr_fd("exit\n", 2);
	state = NULL;
	exit(status);
}

int	ft_exit(char *line, char *msg, t_state *state)
{
	state->error = 258;
	free(line);
	ft_error_message(msg);
	return (0);
}
