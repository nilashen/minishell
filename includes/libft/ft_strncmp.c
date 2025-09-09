/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakunwar <nakunwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:01:40 by nakunwar          #+#    #+#             */
/*   Updated: 2025/03/20 15:09:19 by nakunwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((i < n) && s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// #include<stdio.h>
// #include<string.h>
// int main ()
// {
// 	int a;
// 	a = ft_strncmp("njKdon", "njkdon", 10);
// 	printf("%d", a);
// 	printf("%d", strncmp("njKdon", "njkdon", 10));
// }