/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:37 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:43 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*temp_str;
	unsigned char		ch;
	size_t				index;

	temp_str = (unsigned char *)s;
	ch = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (*(temp_str + index) == ch)
			return ((void *)(temp_str + index));
		index++;
	}
	return (NULL);
}
