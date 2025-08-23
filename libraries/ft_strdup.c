/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:07:57 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:56:02 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr_str;
	size_t	lenght;

	lenght = ft_strlen(s1) + 1;
	ptr_str = (char *)malloc(lenght);
	if (ptr_str == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(ptr_str, s1, lenght);
	return (ptr_str);
}
