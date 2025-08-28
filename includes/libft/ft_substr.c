#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	str_lenght;
	size_t	index;

	if (s == NULL)
		return (NULL);
	str_lenght = ft_strlen(s);
	if ((size_t)start >= str_lenght)
		return (ft_strdup (""));
	if (len > str_lenght - (size_t)start)
		len = str_lenght -(size_t)start;
	sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (NULL);
	index = 0;
	while (index < len && *(s + (size_t)start + index))
	{
		*(sub_str + index) = *(s + (size_t)start + index);
		index++;
	}
	*(sub_str + index) = '\0';
	return (sub_str);
}
