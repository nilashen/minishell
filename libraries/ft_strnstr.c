/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:12 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:56:37 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	core_index;
	size_t	sub_index;

	if (*needle == '\0')
		return ((char *)haystack);
	core_index = 0;
	while ((core_index < len) && *(haystack + core_index) != '\0')
	{
		sub_index = 0;
		while (*(needle + sub_index) && (core_index + sub_index < len))
		{
			if (*(haystack + sub_index + core_index) != *(needle + sub_index))
				break ;
			sub_index++;
		}
		if (*(needle + sub_index) == '\0')
			return ((char *)haystack + core_index);
		core_index++;
	}
	return (NULL);
}
