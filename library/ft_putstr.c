/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:14:54 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:48 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
	{
		return (write(1, "(null)", 6));
	}
	while (*(s + count) != '\0')
	{
		if (write(1, (s + count), 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}
