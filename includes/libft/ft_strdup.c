#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr_str;
	size_t	lenght;

	lenght = ft_strlen(s1) + 1;
	ptr_str = (char *)malloc(lenght);
	if (ptr_str == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(ptr_str, s1, lenght);
	return (ptr_str);
}
