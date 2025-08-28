/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:48:53 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:49 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	ft_get_word(char **result, size_t i, char const *s, char c)
{
	size_t	word_len;
	char	*word;

	word_len = ft_word_len(s, c);
	word = malloc(word_len + 1);
	if (!word)
	{
		while (i-- > 0)
			free(result[i]);
		free(result);
		return (0);
	}
	word_len = ft_strlcpy(word, s, word_len + 1);
	result[i] = word;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_get_word(result, i++, s, c))
				return (NULL);
			s += ft_word_len(s, c);
		}
	}
	result[i] = NULL;
	return (result);
}
// int	main()
// {
// 	char	**split;
// 	const char	*s = "Hello NJK";
// 	char	c = ' ';
// 	int i = 0;
// 	split = ft_split(s, c);
// 	while(split[i])
// 	{
// 		printf("%d: \"%s\"\n",i, split[i]);
// 		i++;
// 	}
// 	return (0);
// }