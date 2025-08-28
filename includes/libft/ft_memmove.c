/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:39:33 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:30 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *ptr1, const void *ptr2, size_t n)
{
	size_t	i;

	if (!ptr1 && !ptr2)
		return (NULL);
	if ((unsigned char *)ptr1 < (unsigned char *)ptr2)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)ptr1)[i] = ((unsigned char *)ptr2)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)ptr1)[i - 1] = ((unsigned char *)ptr2)[i - 1];
			i--;
		}
	}
	return (ptr1);
}
// #include <stdio.h>
// #include <string.h>

// // void *ft_memmove(void *ptr1, const void *ptr2, size_t n);
// int main() {
//     char str[] = "Hello, World!";
//     memmove(str, str + 7, 7); // Copy "World!" to the left
//     printf("Result: %s\n", str);
//     return 0;
// }