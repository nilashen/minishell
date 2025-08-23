/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:09 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:00 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	accumulator;

	sign = 1;
	while (*str == 32 || ((*str >= 9) && (*str <= 13)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	accumulator = 0;
	while (*str >= 48 && *str <= 57)
	{
		accumulator = accumulator * 10 + (*str - 48);
		str++;
	}
	return (accumulator = sign * accumulator);
}
