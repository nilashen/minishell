#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	srclenght;

	index = 0;
	srclenght = 0;
	while (*(src + srclenght) != '\0')
		srclenght++;
	if (dstsize == 0)
		return (srclenght);
	while ((index < dstsize - 1) && (*(src + index) != '\0'))
	{
		*(dst + index) = *(src + index);
		index ++;
	}
	*(dst + index) = '\0';
	return (srclenght);
}
