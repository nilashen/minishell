/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:21:47 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:24 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>

// // int ft_memcmp(const void *ptr1, const void *ptr2, size_t n);

// int main() {
//     const char *str1 = "1234567";
//     const char *str2 = "12345678901400345678";
//     int result = memcmp(str1, str2, 10);

//     printf("Result: %d\n", result); // Expected: 0
//     printf("%d", ft_memcmp(str1, str2, 10));
//     return 0;
// }
