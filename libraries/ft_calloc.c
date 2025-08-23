/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:18 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:14 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	totalsize;

	totalsize = count * size;
	if (((count != 0) && (size != 0)) && ((count * size) < totalsize))
		return (NULL);
	ptr = (void *)malloc(totalsize);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero (ptr, totalsize);
	return (ptr);
}
