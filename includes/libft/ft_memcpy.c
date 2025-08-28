#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d_ptr;
	const unsigned char	*s_ptr;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	if (n == 0)
		return (dst);
	d_ptr = (unsigned char *)dst;
	s_ptr = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	return (dst);
}
