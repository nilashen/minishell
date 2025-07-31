/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:02:09 by nashena           #+#    #+#             */
/*   Updated: 2025/07/31 11:38:15 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../library/libutils.h"
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
void	mysh_echo(char **argv);
int		mysh_pwd(void);
int		mysh_cd(char **argv);

#endif