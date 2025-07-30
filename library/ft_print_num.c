/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:10:34 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:06 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

int	ft_print_id(int num)
{
	int	print_count;

	print_count = 0;
	if (num == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (num < 0)
	{
		write(1, "-", 1);
		num = -1 * num;
		print_count++;
	}
	if (num >= 10)
		print_count += ft_print_id(num / 10);
	print_count++;
	num = (num % 10) + 48;
	ft_putchar(num);
	return (print_count);
}
