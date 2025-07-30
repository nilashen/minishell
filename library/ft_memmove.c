/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:47 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:54 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*temp_dst;
	const unsigned char	*temp_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	temp_dst = (unsigned char *)dst;
	temp_src = (const unsigned char *)src;
	if (temp_dst < temp_src)
	{
		while (len--)
		{
			*temp_dst++ = *temp_src++;
		}
	}
	else
	{
		temp_dst += len;
		temp_src += len;
		while (len--)
		{
			*--temp_dst = *--temp_src;
		}
	}
	return (dst);
}
