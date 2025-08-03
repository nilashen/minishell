/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:02:09 by nashena           #+#    #+#             */
/*   Updated: 2025/08/03 13:34:55 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "library/libutils.h"
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
int		mysh_echo(char **argv);
int		mysh_pwd(void);
int		mysh_cd(char **argv);
int		mysh_env(char **envp);
int		mysh_exit(char **argv);
int		main(int argc, char **argv, char **envp);
int		mysh_export(char **args, char ***envp);
int		env_set(char ***envp, char *key, char *value);
int		mysh_unset(char **argv, char ***envp);
int		env_unset(char ***envp, char *key);
#endif