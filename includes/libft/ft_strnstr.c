/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:25:31 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:09:23 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (i + j < len && haystack[i + j] && needle[j]
				&& haystack[i + j] == needle[j])
				j++;
			if (!needle[j])
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
// #include <string.h>

// int main()
// {
//     const char *haystack = "Hello, world!";
//     const char *needle = "l";
//     char *result = ft_strnstr(haystack, needle, 2);
//     if (result)
//         printf("Substring found: %s\n", result);
//     else
//         printf("Substring not found.\n");

//     return 0;
// }