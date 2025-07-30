/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:50 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:58 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buff_temp ;
	unsigned char	amount;
	size_t			index;

	buff_temp = (unsigned char *)b;
	amount = (unsigned char)c;
	index = 0;
	while (index < len)
	{
		*(buff_temp + index) = amount;
		index++;
	}
	return (b);
}
