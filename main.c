#include "./includes/minishell.h"

int g_sig_status;

static void	ft_init_program(int argc, char **argv, char **envp, t_state **state)
{
	(void)argv;
	if (argc > 1)
	{
		ft_error_message("Invalid argument!");
		exit(1);
	}
	*state = (t_state *)malloc(sizeof(t_state));
	(*state)->pars = malloc(sizeof(t_parser));
	if (!(*state)->pars || !(*state))
		ft_error_message("Error: Malloc problem !");
	g_sig_status = 0;
	ft_init_signals();
	(*state)->env = ft_get_env(*state, envp);
	(*state)->exp = ft_get_env(*state, envp);
	(*state)->envp = envp;
	(*state)->error = 0;
	(*state)->cluster = NULL;
	(*state)->fd = NULL;
}

static char	*ft_get_input_line(void)
{
    char	*line;
    char	*result;

    if (isatty(fileno(stdin)))
    {
        line = readline("minishell $ ");
        // Handle Ctrl+D (EOF) - readline returns NULL
        if (!line)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            return (NULL);
        }
        return (line);
    }
    
    line = get_next_line(fileno(stdin));
    if (!line)
        return (NULL);
    result = ft_strtrim(line, "\n");
    free(line);
    return (result);
}

static void	ft_setup_loop_iteration(t_state *state)
{
	g_sig_status = 0;
	ft_separate_path(state);
	state->pars->ptr_errno = &(state->error);
	state->line = ft_get_input_line();
}

static int	ft_handle_command_processing(t_state *state, int *final_exit_code)
{
	int	parser_result;

	if (state->line && ft_wait_for_input(state) == 1)
		add_history(state->line);
	parser_result = ft_parser(state);
	if (parser_result)
	{
		*final_exit_code = state->error;
		ft_free_double_str(state->sep_path);
        free(state->line);
        ft_all_cluster_free(state);
        return (1);
	}
	*final_exit_code = state->error;
	ft_free_double_str(state->sep_path);
	free(state->line);
	ft_all_cluster_free(state);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
    t_state	*state;
    int		final_exit_code;

    ft_init_program(argc, argv, envp, &state);
    final_exit_code = 0;
    
    while (1)
    {
        ft_setup_loop_iteration(state);
        if (!state->line) // EOF (Ctrl+D) - exit cleanly
            break;
        ft_handle_command_processing(state, &final_exit_code);
    }
    ft_full_free(state, final_exit_code);
    return (final_exit_code);
}
