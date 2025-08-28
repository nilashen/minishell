#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*temp_dst;
	const unsigned char	*temp_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	temp_dst = (unsigned char *)dst;
	temp_src = (const unsigned char *)src;
	if (temp_dst < temp_src)
	{
		while (len--)
		{
			*temp_dst++ = *temp_src++;
		}
	}
	else
	{
		temp_dst += len;
		temp_src += len;
		while (len--)
		{
			*--temp_dst = *--temp_src;
		}
	}
	return (dst);
}
