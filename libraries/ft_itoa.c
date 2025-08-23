/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:17:35 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:37 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

int	ft_countdig(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t			count;
	size_t			index;
	char			*amount;
	unsigned int	num;

	count = ft_countdig (n);
	amount = (char *)malloc(count + 1);
	if (amount == NULL)
		return (NULL);
	index = 0;
	if (n < 0)
	{
		*(amount + index++) = '-';
		num = -n;
	}
	else
		num = n;
	*(amount + count) = '\0';
	while (count > index)
	{
		*(amount + --count) = (num % 10) + '0';
		num /= 10;
	}
	return (amount);
}
