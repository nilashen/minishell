/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:09:27 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 16:09:31 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lens1;
	char	*dst;

	lens1 = ft_strlen(s1);
	i = -1;
	dst = malloc(sizeof(char) * (lens1 + ft_strlen(s2) + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[++i])
		dst[i] = (char )s1[i];
	i = -1;
	while (s2[++i])
	{
		dst[lens1] = s2[i];
		lens1++;
	}
	dst[lens1] = '\0';
	return (dst);
}
// #include<stdio.h>
// int main()
// {
// 	char * str1 = ft_strjoin("ftufh", "hdrhd");
// 	// char str2[] = "World!";
// 	printf("%s\n", str1);
// }