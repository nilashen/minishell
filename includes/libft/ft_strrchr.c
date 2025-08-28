/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:25:19 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:09:25 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	count;
	char	*cs;

	i = 0;
	count = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
		{
			cs = (char *) s + i;
			count = 1;
		}
		i++;
	}
	if (count > 0)
		return (cs);
	return (0);
}
// int main() {
//     const char *str = "Hello, World!";
//     char *result = ft_strrchr(str, '\0');

//     if (result)
//         printf("Character found: %s\n", result);
//     else
//         printf("Character not found.\n");

//     return 0;
// }