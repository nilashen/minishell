/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:23:01 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:55:44 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	index;

	index = 0;
	while (*(s + index) != '\0')
	{
		write (fd, (s + index), 1);
		index++;
	}
}
