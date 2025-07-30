/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:11:25 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 19:06:39 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libutils.h"

void	echo(char **argv)
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