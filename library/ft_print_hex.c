/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:10:29 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:02 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

int	ft_puthex(unsigned int num, const char *str)
{
	int				print_count;
	unsigned int	nb;
	char			*hex_str;

	if (*str == 'x')
		hex_str = "0123456789abcdef";
	else if (*str == 'X')
		hex_str = "0123456789ABCDEF";
	print_count = 0;
	nb = (unsigned int)num;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else if (nb >= 16)
		print_count += ft_puthex(nb / 16, str);
	print_count++;
	ft_putchar(hex_str[nb % 16]);
	return (print_count);
}
