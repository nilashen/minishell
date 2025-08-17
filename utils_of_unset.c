/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:39:48 by nashena           #+#    #+#             */
/*   Updated: 2025/08/17 20:17:41 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_identifier(const char *name)
{
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
    name++;
    while (*name)
    {
        if (!ft_isalnum(*name) && *name != '_')
            return (0);
        name++;
    }
    return (1);
}

static int find_env_var_index(char **envp, const char *key)
{
    int i;
    int key_len;

    if (!envp || !key)
        return (-1);
    key_len = ft_strlen(key);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, key_len) == 0 && 
            envp[i][key_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}
static int remove_env_var_at_index(char ***envp, int index)
{
    char **env;
    int count;
    int i;

    if (!envp || !*envp || index < 0)
        return (-1);
    env = *envp;
    count = env_count(env);
    if (index >= count)
        return (-1);
    free(env[index]);
    i = index;
    while (i < count - 1)
    {
        env[i] = env[i + 1];
        i++;
    }
    env[count - 1] = NULL;
    return (0);
}

int env_unset(char ***envp, char *key)
{
    int index;

    if (!envp || !*envp || !key)
        return (-1);
    if (!is_valid_identifier(key))
    {
        ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
        ft_putstr_fd(key, STDERR_FILENO);
        ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	    return (-1);
    }
    index = find_env_var_index(*envp, key);
    if (index == -1)
        return (0);
    return (remove_env_var_at_index(envp, index));
}
