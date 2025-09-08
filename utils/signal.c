#include "../includes/minishell.h"

static void	ft_signal_handler(int sig)
{
    const char newline[] = "\n";
    
    (void)sig;
    if (g_sig_status == IN_CAT)
    {
        write(STDOUT_FILENO, newline, 1);
        rl_on_new_line();
    }
    else if (g_sig_status == IN_HERADOC)
    {
        write(STDOUT_FILENO, newline, 1);
        exit(1);
    }
    else if (g_sig_status == 0)
    {
        write(STDOUT_FILENO, newline, 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    g_sig_status = 0;
}

void	ft_init_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
