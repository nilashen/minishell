#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	lenght;
	size_t	index;
	char	*map_string;

	if (s == NULL || f == NULL)
		return (NULL);
	lenght = ft_strlen(s);
	map_string = (char *) malloc (lenght + 1);
	if (map_string == NULL)
		return (NULL);
	index = 0;
	while (index < lenght)
	{
		*(map_string + index) = f(index,*(s + index));
		index++;
	}
	*(map_string + lenght) = '\0';
	return (map_string);
}
