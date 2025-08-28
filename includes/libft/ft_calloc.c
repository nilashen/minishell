#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	totalsize;

	totalsize = count * size;
	if (((count != 0) && (size != 0)) && ((count * size) < totalsize))
		return (NULL);
	ptr = (void *)malloc(totalsize);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero (ptr, totalsize);
	return (ptr);
}
