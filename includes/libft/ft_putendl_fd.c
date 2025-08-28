/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:09:08 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:40 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s && fd >= 0)
	{
		write (fd, s, ft_strlen(s));
		write (fd, "\n", 1);
	}
}
// #include<stdio.h>
// int main ()
// {
// 	char str[] = "Hello World!";
// 	ft_putendl_fd(str, 0);
// 	return (0);
// }