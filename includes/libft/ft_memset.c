#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buff_temp ;
	unsigned char	amount;
	size_t			index;

	buff_temp = (unsigned char *)b;
	amount = (unsigned char)c;
	index = 0;
	while (index < len)
	{
		*(buff_temp + index) = amount;
		index++;
	}
	return (b);
}
