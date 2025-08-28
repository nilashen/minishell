#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	size_t	lenght;

	lenght = ft_strlen(s);
	index = lenght ;
	while (index > 0)
	{
		index--;
		if (*(s + index) == (char)c)
			return ((char *)(s + index));
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + lenght));
	}
	return (NULL);
}
