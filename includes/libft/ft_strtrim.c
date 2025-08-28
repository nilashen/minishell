/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:31:56 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 16:09:35 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_in_set(s1[start], set))
		start++;
	while (end > start && ft_in_set(s1[end - 1], set))
		end--;
	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
// int	main()
// {
// 		char	*strtrim;
// 		char s1[] = "  Hello NJK";
// 		if (!(strtrim = ft_strtrim(s1, "	")))
// 			printf("Error");
// 		else
// 			printf("%s\n", strtrim);
// }