/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:18:29 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:56:30 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	lenght;
	size_t	index;
	char	*map_string;

	if (s == NULL || f == NULL)
		return (NULL);
	lenght = ft_strlen(s);
	map_string = (char *) malloc (lenght + 1);
	if (map_string == NULL)
		return (NULL);
	index = 0;
	while (index < lenght)
	{
		*(map_string + index) = f(index,*(s + index));
		index++;
	}
	*(map_string + lenght) = '\0';
	return (map_string);
}
