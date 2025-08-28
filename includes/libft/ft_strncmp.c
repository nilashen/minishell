#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	char1;
	unsigned char	char2;

	index = 0;
	while ((*(s1 + index) || *(s2 + index)) && index < n)
	{
		char1 = (unsigned char)*(s1 + index);
		char2 = (unsigned char)*(s2 + index);
		if (char1 != char2)
			return (char1 - char2);
		index++;
	}
	return (0);
}
