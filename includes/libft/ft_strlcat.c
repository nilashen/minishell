/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:38:31 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:09:05 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *ptr1, const char *ptr2, size_t n)
{
	size_t	i;
	size_t	ptr1_len;
	size_t	ptr2_len;

	i = 0;
	ptr1_len = 0;
	ptr2_len = 0;
	while (ptr1[ptr1_len] && ptr1_len < n)
		ptr1_len++;
	while (ptr2[ptr2_len])
		ptr2_len++;
	if (ptr1_len >= n)
		return (n + ptr2_len);
	while (ptr2[i] && ((ptr1_len + i + 1) < n))
	{
		ptr1[ptr1_len + i] = ptr2[i];
		i++;
	}
	ptr1[ptr1_len + i] = '\0';
	return (ptr1_len + ptr2_len);
}
// #include<stdio.h>
// #include<string.h>
// int	main(void)
// {
// 	const char	src[] = "123456";
// 	char		dst[3] = "789";
// 	printf("before: %s\n", dst);
// 	int len = strlcat(dst, src, sizeof(dst));
// 	printf("after: %s\n", dst);
//     printf("len : %d", len);
// 	return (0);
// }