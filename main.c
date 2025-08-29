#include "includes/minishell.h"

int g_sig_status;

static void	ft_validate_args(int argc)
{
	if (argc > 1)
	{
		ft_error_mesage("Invalid argument!");
		exit(1);
	}
}

static t_state	*ft_allocate_state(void)
{
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
	{
		ft_error_mesage("Error: Malloc problem !");
		exit(1);
	}
	state->pars = malloc(sizeof(t_parser));
	if (!state->pars)
	{
		free(state);
		ft_error_mesage("Error: Malloc problem !");
		exit(1);
	}
	return (state);
}

static void	ft_init_state_values(t_state *state, char **envp)
{
	g_sig_status = 0;
	ft_init_signals();
	disable_quit_echo();
	state->env = get_env(state, envp);
	state->exp = get_env(state, envp);
	state->envp = envp;
	state->error = 0;
	state->cluster = NULL;
	state->fd = NULL;
}

// REPLACE only this function
static void	ft_init_program(int argc, char **argv, char **envp, t_state **state)
{
	(void)argv;
	ft_validate_args(argc);
	*state = ft_allocate_state();
	ft_init_state_values(*state, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;

	ft_init_program(argc, argv, envp, &state);
	ft_init_signals();
	while (1)
	{
		g_sig_status = 0;
		ft_sep_path(state);
		state->pars->ptr_errno = &(state->error);
		state->line = readline("minishell $ ");
		if (state->line && ft_wait_for_input(state) == 1)
			add_history(state->line);
		if (ft_parser(state))
			break ;
		ft_free_double_str(state->sep_path);
		free(state->line);
		ft_all_cluster_free(state);
	}
	ft_full_free(state, 0);
	return (0);
}
