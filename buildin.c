/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:11:25 by nashena           #+#    #+#             */
/*   Updated: 2025/07/31 11:31:59 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mysh_echo(char **argv)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (argv[1] && (ft_strcmp(argv[1], "-n") == 0))
	{
		newline = 0;
		i++;
	}
	i = 0;
	while (argv[i] != NULL)
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
		{
			ft_printf(" ");
		}
		i++;
	}
	if (newline)
	{
		ft_printf("\n");
	}
}
int	mysh_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
int	mysh_cd(char **argv)
{
	char	*path;

	if (!argv[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
