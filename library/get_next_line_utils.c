/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:26 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:57:09 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;
	size_t			dst_index;
	size_t			src_index;

	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dst);
	dst_index = 0;
	src_index = 0;
	while (n > 0)
	{
		if (*(temp_dst + dst_index) != *(temp_src + src_index))
			*(temp_dst + dst_index) = *(temp_src + src_index);
		dst_index++;
		src_index++;
		n--;
	}
	return (dst);
}

char	*ft_strjoin(char const *temp_storage, char const *buffer)
{
	size_t	stash_len;
	size_t	buffer_len;
	char	*result;

	if (!buffer && !temp_storage)
		return (NULL);
	stash_len = ft_strlen(temp_storage);
	buffer_len = ft_strlen(buffer);
	result = (char *)malloc(stash_len + buffer_len + 1);
	if (!result)
		return (NULL);
	if (temp_storage)
		ft_memcpy(result, temp_storage, stash_len);
	ft_memcpy(result + stash_len, buffer, buffer_len + 1);
	return (result);
}
