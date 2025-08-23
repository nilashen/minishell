/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:14 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:54:10 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp_srt;
	size_t			index;

	temp_srt = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		*(temp_srt + index) = 0;
		index++;
	}
}
