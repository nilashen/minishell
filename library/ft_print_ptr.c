/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:10:38 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:09 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

int	ft_printptr(unsigned long pnum)
{
	int		print_count;
	char	*hex_str;

	print_count = 0;
	hex_str = "0123456789abcdef";
	if (pnum >= 16)
		print_count += ft_printptr(pnum / 16);
	print_count += ft_putchar(hex_str[pnum % 16]);
	return (print_count);
}

int	ft_putptr(void *pnum)
{
	int				print_count;
	unsigned long	address;

	address = (unsigned long)pnum;
	print_count = 0;
	print_count += write(1, "0x", 2);
	if (address == 0)
	{
		print_count += write(1, "0", 1);
		return (print_count);
	}
	print_count += ft_printptr(address);
	return (print_count);
}
