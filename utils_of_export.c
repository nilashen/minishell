/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:56:24 by nashena           #+#    #+#             */
/*   Updated: 2025/08/20 15:45:18 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static int find_env_var(char **envp, const char *key)
{
    int i;
    int key_len;

    if (!envp || !key)
        return -1;

    key_len = ft_strlen(key);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, key_len) == 0 &&
            (envp[i][key_len] == '=' || envp[i][key_len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}
static char *get_env_value(char **envp, const char *key)
{
    int index;
    char *equal_pos;

    index = find_env_var(envp, key);
    if (index == -1)
        return NULL;

    equal_pos = ft_strchr(envp[index], '=');
    if (equal_pos)
        return (equal_pos + 1);
    return (NULL);
}
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

int print_exported_vars(char **envp)
{
    int i, j, count;
    char **sorted_env;
    char *equal_pos;

    if (!envp)
        return (0);
    count = 0;
    while (envp[count])
        count++;
    if (count == 0)
        return (0);
    sorted_env = malloc(sizeof(char*) * (count + 1));
    if (!sorted_env)
        return (1);
    i = 0;
    while (i < count)
    {
        sorted_env[i] = envp[i];
        i++;
    }
    sorted_env[count] = NULL;
    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - 1 - i)
        {
            if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
            {
                char *temp = sorted_env[j];
                sorted_env[j] = sorted_env[j + 1];
                sorted_env[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < count)
    {
        equal_pos = ft_strchr(sorted_env[i], '=');
        if (equal_pos)
        {
            *equal_pos = '\0';
            printf("declare -x %s=\"%s\"\n", sorted_env[i], equal_pos + 1);
            *equal_pos = '=';
        }
        else
            printf("declare -x %s\n", sorted_env[i]);
        i++;
    }
    free(sorted_env);
    return (0);
}

static int handle_append_assignment(char ***envp, char *key, char *append_value)
{
    char *current_value;
    char *new_value;
    int result;

    current_value = get_env_value(*envp, key);
    if (current_value)
    {
        new_value = malloc(ft_strlen(current_value) + ft_strlen(append_value) + 1);
        if (!new_value)
            return (1);
        ft_strcpy(new_value, current_value);
        ft_strcat(new_value, append_value);
        result = env_set(envp, key, new_value);
        free(new_value);
        return (result);
    }
    else
    {
        return (env_set(envp, key, append_value));
    }
}

int process_export_arg(char ***envp, char *arg)
{
    char *equal_pos;
    char *plus_pos;
    char *key;
    char *value;
    int key_len;
    int result = 0;

    if (!arg || !*arg)
    {
        ft_putstr_fd("minishell: export: not a valid identifier\n", STDERR_FILENO);
        return (1);
    }
    plus_pos = ft_strstr(arg, "+=");
    if (plus_pos)
    {
        key_len = plus_pos - arg;
        key = malloc(key_len + 1);
        if (!key)
            return (1);
        ft_strncpy(key, arg, key_len);
        key[key_len] = '\0';
        if (!is_valid_identifier(key))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(arg, STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            free(key);
            return (1);
        }
        value = plus_pos + 2;
        result = handle_append_assignment(envp, key, value);
        free(key);
        return (result);
    }
    equal_pos = ft_strchr(arg, '=');
    if (equal_pos)
    {
        *equal_pos = '\0';
        key = arg;
        value = equal_pos + 1;
        if (!is_valid_identifier(key))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(arg, STDERR_FILENO);
            ft_putstr_fd("=", STDERR_FILENO);
            ft_putstr_fd(value, STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            *equal_pos = '=';
            return (1);
        }
        result = env_set(envp, key, value);
        *equal_pos = '=';
        return (result);
    }
    else
    {
        if (!is_valid_identifier(arg))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(arg, STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            return (1);
        }
		if (find_env_var(*envp, arg) == -1)
		{
			return env_set(envp, arg, NULL);
		}
		return (0);
    }
}
