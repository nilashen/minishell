/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:27:43 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:27 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *ptr1, const void *ptr2, size_t n)
{
	size_t				i;
	unsigned char		*p1;
	const unsigned char	*p2;

	if (!ptr1 && !ptr2)
		return (NULL);
	p1 = (unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	return (ptr1);
}
// #include <stdio.h>
// #include <string.h>

// void *ft_memcpy(void *ptr1, const void *ptr2, size_t n);

// int main() {
//     char str[] = "Hello, World!";
//     memcpy(str + 5, str, 7); // Overlapping memory regions
//     printf("Result: %s\n", str);

//     return 0;
// }