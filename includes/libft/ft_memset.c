/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:12:01 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:33 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)ptr;
	while (i < n)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}
// int main()
// {
//     unsigned char *str = NULL;
//     ft_memset(str, 'A', 7);
//     printf("%s", str);
// }