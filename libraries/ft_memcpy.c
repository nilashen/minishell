/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:44 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:50 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d_ptr;
	const unsigned char	*s_ptr;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	if (n == 0)
		return (dst);
	d_ptr = (unsigned char *)dst;
	s_ptr = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	return (dst);
}
