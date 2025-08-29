#include "../includes/minishell.h"

static void	ft_signal_handler(int sig)
{
	(void)sig;
	if (g_sig_status == IN_CAT)
	{
		write (STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
	}
	else if (g_sig_status == IN_HERADOC)
	{
		write (STDOUT_FILENO, "\n", 1);
		exit(1);
	}
	else if (g_sig_status == 0)
	{
		write (STDOUT_FILENO, "\n", 1);
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

void	ft_reset_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void disable_quit_echo(void)
{
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
    {
        perror("tcgetattr");
        return;
    }
    term.c_lflag &= ~ECHOCTL;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
    {
        perror("tcsetattr");
        return;
    }
}
