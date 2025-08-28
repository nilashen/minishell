/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:10:38 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:09:11 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *ptr1, const char *ptr2, size_t n)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(ptr2);
	i = 0;
	if (n == 0)
		return (len);
	while (ptr2[i] && (i < (n - 1)))
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	ptr1[i] = '\0';
	return (len);
}
// #include<stdio.h>
// #include<string.h>
// int	main(void)
// {
// 	const char	src[14] = "Hello, World!";
// 	char	dst[10] = "0987654321";
// 	int len = strlcpy(dst, src, 10);
// 	printf("dst: %s\n", dst);
//     printf("len: %d\n", len);
// 	return 0;
// }