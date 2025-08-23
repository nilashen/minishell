/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:53 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:57 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	while (*(s + index) != '\0')
	{
		if (*(s + index) == (char)c)
			return ((char *)(s + index));
		index++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + index));
	}
	return (NULL);
}
