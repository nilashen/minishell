#include "libft.h"

void	ft_initial(int	*start, int *i, size_t *index)
{
	*index = 0;
	*i = 0;
	*start = -1;
}

static size_t	ft_count_sub(char const *str, char ch)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str == ch)
			str++;
		if (*str != '\0')
			count++;
		while (*str != '\0' && *str != ch)
			str++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, int start, int end)
{
	size_t	index;
	char	*ptr_str;

	ptr_str = (char *)malloc((end - start + 1) * sizeof(char));
	if (ptr_str == NULL)
		return (NULL);
	index = 0;
	while (start < end)
	{
		*(ptr_str + index) = *(s + start);
		index++;
		start++;
	}
	*(ptr_str + index) = 0;
	return (ptr_str);
}

static void	*ft_free_all(char **amount, size_t index)
{
	while (index--)
	{
		free(*(amount + index));
	}
	free(amount);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	index;
	char	**splited_str;
	int		i;
	int		start;

	ft_initial(&start, &i, &index);
	splited_str = (char **)malloc(sizeof(char *) * (ft_count_sub(s, c) + 1));
	if (splited_str == NULL)
		return (NULL);
	while (index <= ft_strlen(s))
	{
		if (*(s + index) != c && start < 0)
			start = index;
		else if ((*(s + index) == c || index == ft_strlen (s)) && start >= 0)
		{
			*(splited_str + i) = ft_strndup(s, start, index);
			if (!*(splited_str + i))
				return (ft_free_all(splited_str, i));
			start = -1;
			i++;
		}
		index++;
	}
	splited_str[i] = NULL;
	return (splited_str);
}
