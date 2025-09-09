/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:35:52 by nakunwar          #+#    #+#             */
/*   Updated: 2025/09/09 16:36:04 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_signal_handler(int sig)
{
	if (g_sig_status == IN_CAT)
	{
		if (sig == SIGINT)
			rl_on_new_line();
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
		return ;
	else
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
