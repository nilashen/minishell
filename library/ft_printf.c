/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:10:51 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:19 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

int	ft_parsetype(const char c, va_list amount)
{
	unsigned int	print_count;

	print_count = 0;
	if (c == 'c')
		print_count += ft_putchar(va_arg(amount, int));
	else if (c == 's')
		print_count += ft_putstr(va_arg(amount, char *));
	else if (c == 'd' || c == 'i')
		print_count += ft_print_id(va_arg(amount, int));
	else if (c == 'u')
		print_count += ft_putunsign(va_arg(amount, unsigned int));
	else if (c == 'p')
		print_count += ft_putptr(va_arg(amount, void *));
	else if (c == 'x' || c == 'X')
		print_count += ft_puthex(va_arg(amount, unsigned int), &c);
	else if (c == '%')
		print_count += ft_putchar('%');
	if (print_count < 0)
		return (-1);
	return (print_count);
}

int	ft_printf(const char *str, ...)
{
	int		print_count;
	va_list	arglist;

	print_count = 0;
	va_start(arglist, str);
	while (*str)
	{
		if (*str != '%')
		{
			print_count += ft_putchar(*str);
		}
		else if (*str == '%')
		{
			str++;
			print_count += ft_parsetype(*str, arglist);
		}
		str++;
	}
	va_end(arglist);
	if (print_count < 0)
		return (-1);
	return (print_count);
}
