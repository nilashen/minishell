/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:01:56 by nashena           #+#    #+#             */
/*   Updated: 2025/08/12 16:56:26 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_count(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

static int	handle_cd_failure(char *old_pwd, const char *error_arg)
{
	handle_chdir_error(error_arg);
	free(old_pwd);
	return (1);
}

static char	*resolve_cd_path(char **args, int arg_count, char **envp)
{
		char *home;
		char *oldpwd;

	(void)envp;
	if (arg_count == 1)
	{
		home = getenv("HOME");
		if (!home)
			return (NULL);
		return (home);
	}
	else if (strcmp(args[1], "-") == 0)
	{
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
			return (NULL);
		return (oldpwd);
	}
	else
		return (args[1]);
}

static void	update_pwd_vars(char ***envp, char *old_pwd)
{
	char	*new_pwd;
	char buf[PATH_MAX];
	
	if (getcwd(buf, sizeof(buf)) == NULL)
	return;
	new_pwd = ft_strdup(buf);
    if (!new_pwd)
        return;
	if (old_pwd)
        env_set(envp, "OLDPWD", old_pwd);
    env_set(envp, "PWD", new_pwd);
    free(new_pwd);
}


int process_cd_command(char **args, int arg_count, char ***envp)
{
    char buf[PATH_MAX];
    char *old_pwd;
    char *path;
    const char *error_arg;

    if (getcwd(buf, sizeof(buf)) == NULL)
        old_pwd = NULL;
    else
        old_pwd = ft_strdup(buf);
    path = resolve_cd_path(args, arg_count, *envp);
    if (arg_count >= 2)
        error_arg = args[1];
    else
        error_arg = path;
    if (!path || chdir(path) == -1)
        return handle_cd_failure(old_pwd, error_arg);
    if (arg_count == 2 && ft_strcmp(args[1], "-") == 0)
        ft_printf("%s\n", path);
    update_pwd_vars(envp, old_pwd);
    free(old_pwd);
    return 0;
}
