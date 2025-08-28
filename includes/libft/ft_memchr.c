/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:06:09 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:20 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int search_str, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)ptr;
	while (i < n)
	{
		if (temp[i] == (unsigned char)search_str)
			return ((void *)(temp + i));
		i++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main ()
// {
//    const char str[] = "Tutorialspoint";
//    const char ch = 'i';
//    char *ret;
//    ret = memchr(str, ch, strlen(str));
//    printf("String after |%c| is - |%s|\n", ch, ret);
//    printf("String:- |%s|\n", ch, ft_memchr(str, ch, strlen(str)));
//    return(0);
// }