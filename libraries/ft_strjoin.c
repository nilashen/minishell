/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:41:11 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:56:12 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	lenght1;
	size_t	lenght2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lenght1 = ft_strlen (s1);
	lenght2 = ft_strlen (s2);
	joined_str = (char *)malloc(lenght1 + lenght2 + 1);
	if (joined_str == NULL)
		return (NULL);
	ft_memcpy (joined_str, s1, lenght1);
	ft_memcpy (joined_str + lenght1, s2, lenght2);
	*(joined_str + lenght1 + lenght2) = '\0';
	return (joined_str);
}
