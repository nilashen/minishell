/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_us.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:10:48 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:14 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

unsigned int	ft_putunsign(unsigned int num)
{
	int	print_count;

	print_count = 0;
	if (num > 9)
		print_count += ft_print_id(num / 10);
	print_count++;
	num = num % 10;
	ft_putchar(num + 48);
	return (print_count);
}
