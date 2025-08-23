/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:03 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:56:21 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	srclenght;

	index = 0;
	srclenght = 0;
	while (*(src + srclenght) != '\0')
		srclenght++;
	if (dstsize == 0)
		return (srclenght);
	while ((index < dstsize - 1) && (*(src + index) != '\0'))
	{
		*(dst + index) = *(src + index);
		index ++;
	}
	*(dst + index) = '\0';
	return (srclenght);
}
