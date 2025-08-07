/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:56:18 by nashena           #+#    #+#             */
/*   Updated: 2025/08/07 10:28:52 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_executable(char *path)
{
	struct stat	sb;

	if (access(path, F_OK) == 0)
	{
		if (stat(path, &sb) == 0 && S_ISREG(sb.st_mode))
		{
			if (access(path, X_OK) == 0)
				return (ft_strdup(path));
		}
	}
	return (NULL);
}

static char	*search_in_path(char *cmd, char *path_env)
{
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			i++;
			continue ;
		}
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (full_path && check_executable(full_path))
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);
}

char	*find_executable_path(char *cmd, char **envp)
{
	char *path_env;
	char *result;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_executable(cmd));
	path_env = env_get(envp, "PATH");
	if (!path_env)
		return (NULL);
	result = search_in_path(cmd, path_env);
	return (result);
}