#include "../includes/minishell.h"

static void	ft_signal_handler(int sig)
{
    if (g_sig_status == IN_CAT)
    {
        if (sig == SIGINT)
        {
            write(STDOUT_FILENO, "\n", 1);
            rl_on_new_line();
            // Don't reset g_sig_status here, let the parent process handle it
        }
    }
    else if (g_sig_status == IN_HEREDOC)
    {
        if (sig == SIGINT)
        {
            write(STDOUT_FILENO, "\n", 1);
            exit(130); // Standard bash exit code for SIGINT
        }
    }
    else if (g_sig_status == 0)  // Interactive mode
    {
        if (sig == SIGINT)
        {
            write(STDOUT_FILENO, "\n", 1);
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
        }
    }
}

void	ft_init_signals(void)
{
    signal(SIGINT, ft_signal_handler);
    signal(SIGQUIT, SIG_IGN);
}

// void	ft_init_signals(void)
// {
// 	signal(SIGINT, ft_signal_handler);
// 	signal(SIGTSTP, SIG_IGN);
//     signal(SIGQUIT, SIG_IGN); 
// }
