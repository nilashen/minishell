#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp_srt;
	size_t			index;

	temp_srt = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		*(temp_srt + index) = 0;
		index++;
	}
}
