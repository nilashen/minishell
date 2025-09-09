#include "../includes/minishell.h"

static void	ft_signal_handler(int sig)
{
    if (g_sig_status == IN_CAT)
    {
        if (sig == SIGINT)
        {
            // Don't write newline here - let the child process handle it
            // The newline will be printed when the process terminates
            rl_on_new_line();
        }
        // SIGQUIT will be handled by child process
    }
    else if (g_sig_status == IN_HEREDOC)
    {
        if (sig == SIGINT)
        {
            write(STDOUT_FILENO, "\n", 1);
            exit(130);
        }
    }
    else if (g_sig_status == IN_PARENT)
    {
        // Parent waiting - do nothing, let child handle
        return;
    }
    else // Interactive mode (g_sig_status == 0)
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
    // Handle SIGINT with custom handler
    signal(SIGINT, ft_signal_handler);
    
    // IGNORE SIGQUIT completely in interactive mode
    signal(SIGQUIT, SIG_IGN);
}
