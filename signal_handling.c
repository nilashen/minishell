/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:07:38 by nashena           #+#    #+#             */
/*   Updated: 2025/08/17 20:13:33 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile t_signal g_sig = {0, 0, 0, 0};
void	signal_handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_sig.sigint_received = 1;
		g_sig.exit_status = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_sig.sigint_received = 1;
		g_sig.exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_sig.sigquit_received = 1;
		g_sig.exit_status = 131;
		write(STDOUT_FILENO, "Quit: 3\n", 8);
	}
}

void	setup_interactive_signals(void)
{
	struct sigaction sa_int, sa_quit;
	sa_int.sa_handler = signal_handler_interactive;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	g_sig.pid = 0;
}

void	setup_child_signals(void)
{
	struct sigaction sa_int, sa_quit;
	sa_int.sa_handler = signal_handler_child;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_handler = signal_handler_child;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	restore_default_signals(void)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}

void	set_child_pid(pid_t pid)
{
	g_sig.pid = pid;
	if (pid != 0)
		setup_child_signals();
	else
		setup_interactive_signals();
}

int	get_exit_status(void)
{
	return (g_sig.exit_status);
}

void	set_exit_status(int status)
{
	g_sig.exit_status = status;
}

int	check_sigint(void)
{
	int	received;

	received = g_sig.sigint_received;
	g_sig.sigint_received = 0;
	return (received);
}

int	check_sigquit(void)
{
	int	received;

	received = g_sig.sigquit_received;
	g_sig.sigquit_received = 0;
	return (received);
}

void	handle_post_execution_signals(void)
{
	if (g_sig.sigint_received)
	{
		if (g_sig.pid != 0)
			g_sig.exit_status = 130;
		else
			g_sig.exit_status = 1;
		g_sig.sigint_received = 0;
	}
	if (g_sig.sigquit_received)
	{
		g_sig.exit_status = 131;
		g_sig.sigquit_received = 0;
	}
	g_sig.pid = 0;
	setup_interactive_signals();
}

void	init_signals(void)
{
	g_sig.pid = 0;
	g_sig.exit_status = 0;
	g_sig.sigint_received = 0;
	g_sig.sigquit_received = 0;
	setup_interactive_signals();
}

void	cleanup_signals(void)
{
	restore_default_signals();
}
