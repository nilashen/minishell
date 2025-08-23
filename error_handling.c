/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:21:24 by nashena           #+#    #+#             */
/*   Updated: 2025/08/12 17:12:24 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void	handle_getcwd_error(void)
{
	if (errno == EACCES)
		ft_putstr_fd("pwd: cannot access parent directories: Permission denied\n", STDERR_FILENO);
	else if (errno == ENOENT)
		ft_putstr_fd("pwd: cannot access parent directories: No such file or directory\n", STDERR_FILENO);
	else if (errno == ENOMEM)
		ft_putstr_fd("pwd: cannot get current directory: Cannot allocate memory\n", STDERR_FILENO);
	else if (errno == ENAMETOOLONG)
		ft_putstr_fd("pwd: cannot get current directory: File name too long\n", STDERR_FILENO);
	else if (errno == ERANGE)
		ft_putstr_fd("pwd: cannot get current directory: Result too large\n", STDERR_FILENO);
	else
		perror("pwd");
}

void handle_chdir_error(const char *arg)
{
    if (errno == ENOENT)
        ft_printf("cd: %s: No such file or directory\n", arg);
    else if (errno == EACCES)
        ft_printf("cd: %s: Permission denied\n", arg);
    else if (errno == ENOTDIR)
        ft_printf("cd: %s: Not a directory\n", arg);
    else
        ft_printf("cd: %s: %s\n", arg, strerror(errno));
}