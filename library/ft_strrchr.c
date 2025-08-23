/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:22 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:56:41 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	size_t	lenght;

	lenght = ft_strlen(s);
	index = lenght ;
	while (index > 0)
	{
		index--;
		if (*(s + index) == (char)c)
			return ((char *)(s + index));
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + lenght));
	}
	return (NULL);
}
