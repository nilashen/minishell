/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:04:59 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:45 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s && fd >= 0)
		write (fd, s, ft_strlen(s));
}
// #include <stdio.h>
// int main()
// {
//     char str[] = "Hello World!";
//     ft_putstr_fd(str, 1);  // Output: "Hello World!\n"
//     return 0;
// }