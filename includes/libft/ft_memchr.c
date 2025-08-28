
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*temp_str;
	unsigned char		ch;
	size_t				index;

	temp_str = (unsigned char *)s;
	ch = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (*(temp_str + index) == ch)
			return ((void *)(temp_str + index));
		index++;
	}
	return (NULL);
}
