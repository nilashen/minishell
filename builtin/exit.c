#include "../includes/minishell.h"

void ft_builtin_exit(t_state *state, t_cluster *cluster)
{
    int i = -1;

    // ft_putendl_fd("exit", STDOUT_FILENO);
    if (cluster->cmd[1] && cluster->cmd[2])
    {
        // ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        state->error = 1;
        return;
    }
    if (cluster->cmd[1])
    {
        while (cluster->cmd[1][++i])
        {
            if (!ft_isdigit(cluster->cmd[1][i]) && (cluster->cmd[1][i] != '-' || i != 0))
            {
                // ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
                // ft_putstr_fd(cluster->cmd[1], STDERR_FILENO);
                // ft_putendl_fd(": numeric argument required", STDERR_FILENO);
                ft_full_free(state, 255);
            }
        }
        ft_full_free(state, ft_atoi(cluster->cmd[1]));
    }
    ft_full_free(state, state->error);
}
