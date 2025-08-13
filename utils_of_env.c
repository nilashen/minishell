/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:10:24 by nashena           #+#    #+#             */
/*   Updated: 2025/08/13 15:59:37 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_set(char ***envp, char *key, char *value)
{
	char **new_env;
	char *new_var;
	char *temp;
	int i;
	int found;

	if (!envp || !key)
		return (-1);
		if (value == NULL)
		{
			new_var = ft_strdup(key);
			if (!new_var)
				return (-1);
		}
		else
		{
			temp = ft_strjoin(key, "=");
			if (!temp)
				return (-1);
			new_var = ft_strjoin(temp, value);
			free(temp);
			if (!new_var)
				return (-1);
		}
	i = 0;
	found = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0
			&& ((*envp)[i][ft_strlen(key)] == '=' || (*envp)[i][ft_strlen(key)] == '\0'))
		{
			free((*envp)[i]);
			(*envp)[i] = new_var;
			found = 1;
			break ;
		}
		i++;
	}
	if (!found)
	{
		new_env = malloc(sizeof(char *) * (env_count(*envp) + 2));
		if (!new_env)
		{
			free(new_var);
			return (-1);
		}
		i = 0;
		while ((*envp)[i])
		{
			new_env[i] = (*envp)[i];
			i++;
		}
		new_env[i] = new_var;
		new_env[i + 1] = NULL;
		free(*envp);
		*envp = new_env;
	}
	return (0);
}

int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}
int	env_unset(char ***envp, char *key)
{
	int		i;
	int		j;
	int		key_len;
	char	**new_env;
	int		count;

	if (!envp || !*envp || !key)
		return (-1);
	key_len = ft_strlen(key);
	count = env_count(*envp);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (-1);
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (!(ft_strncmp((*envp)[i], key, key_len) == 0 &&
			(*envp)[i][key_len] == '='))
		{
			new_env[j] = (*envp)[i];
			j++;
		}
		else
			free((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}
