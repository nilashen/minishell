/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:25:22 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:40 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write (fd, "-", 1);
		write (fd, "2147483648", 10);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -1 * n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd (n / 10, fd);
	}
	c = (n % 10) + 48;
	write (fd, &c, 1);
}
