#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst - src > 0)
	{
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		return ((void *)dst);
	}
	return (ft_memcpy(dst, src, len));
}
