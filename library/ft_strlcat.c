/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:00 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:56:16 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_lenght;
	size_t	src_lenght;
	size_t	index;

	dest_lenght = 0;
	while ((dest_lenght < dstsize) && *(dst + dest_lenght) != '\0')
	{
		dest_lenght++;
	}
	src_lenght = 0;
	while (*(src + src_lenght) != '\0')
	{
		src_lenght++;
	}
	if (dest_lenght == dstsize)
		return (dest_lenght + src_lenght);
	index = 0;
	while (*(src + index) != '\0' && (dest_lenght + index) < (dstsize - 1))
	{
		*(dst + dest_lenght + index) = *(src + index);
		index++;
	}
	*(dst + dest_lenght + index) = '\0';
	return (dest_lenght + src_lenght);
}
