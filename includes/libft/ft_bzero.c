/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:59:44 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:07:49 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*str1;

	i = 0;
	str1 = (unsigned char *)str;
	while (i < n)
	{
		str1[i] = 0;
		i++;
	}
}
// #include <stdio.h>
// #include <strings.h> // For bzero

// int main() {
//     char str[] = "Hello, World!";

//     printf("Before ft_bzero: %s\n", str);
//     ft_bzero(str, sizeof(str)); // Zero out the string
//     printf("After ft_bzero: %s\n", str);

//     return 0;
// }