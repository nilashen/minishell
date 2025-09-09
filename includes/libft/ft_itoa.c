/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:40:55 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:17 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_handle_zero(void)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static void	ft_fill_str(char *str, int n, int sign, int len)
{
	int	i;

	i = len + (sign < 0);
	str[i--] = '\0';
	while (n)
	{
		str[i--] = '0' - (n % 10);
		n /= 10;
	}
	if (sign < 0)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	if (n == 0)
		return (ft_handle_zero());
	sign = 1;
	if (n < 0)
		sign = -1;
	else
		n = -n;
	len = ft_numlen(n);
	str = malloc(len + (sign < 0) + 1);
	if (!str)
		return (NULL);
	ft_fill_str(str, n, sign, len);
	return (str);
}
// #include <stdio.h>
// int main()
// {
// 	// int num = 2147483647;
// 	int num = -2147483647;
// 	printf("Output: %s\n",  ft_itoa(num));
// }