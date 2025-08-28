/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:09:12 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:43 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd ('-', fd);
		ft_putchar_fd ('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd ('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd((int)n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}
// #include<stdio.h>
// int main ()
// {
// 	ft_putnbr_fd(-2147483648, 1);
// 	printf("\n");
// 	ft_putnbr_fd(2147483647, 1);
// 	printf("\n");
// 	ft_putnbr_fd(42, 1);
// 	printf("\n");
// 	return 0;
// }