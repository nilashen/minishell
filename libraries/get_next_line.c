/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:31 by nashena           #+#    #+#             */
/*   Updated: 2025/07/30 09:57:13 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_update_stash(int fd, char *temp_storage, ssize_t *read_count)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp_buff;

	*read_count = read(fd, buffer, BUFFER_SIZE);
	if (*read_count == -1)
	{
		free(temp_storage);
		return (NULL);
	}
	buffer[*read_count] = '\0';
	temp_buff = ft_strjoin(temp_storage, buffer);
	if (!temp_buff)
	{
		free(temp_storage);
		return (NULL);
	}
	free(temp_storage);
	return (temp_buff);
}

char	*ft_get_whole_line(int fd, char *temp_storage)
{
	ssize_t	read_count;

	read_count = 1;
	while (!ft_strchr(temp_storage, '\n') && read_count > 0)
	{
		temp_storage = ft_update_stash(fd, temp_storage, &read_count);
		if (temp_storage == NULL)
			return (NULL);
	}
	return (temp_storage);
}

char	*ft_extract_line(char *temp_storage)
{
	size_t	index;
	char	*buffer;

	index = 0;
	if (!temp_storage || !(*(temp_storage + index)))
		return (NULL);
	while (*(temp_storage + index) && *(temp_storage + index) != '\n')
		index++;
	if (*(temp_storage + index) == '\n')
		index++;
	buffer = (char *)malloc(index + 1);
	if (buffer == NULL)
		return (NULL);
	ft_memcpy(buffer, temp_storage, index);
	*(buffer + index) = '\0';
	return (buffer);
}

char	*ft_renew_buffer(char *temp_storage)
{
	size_t	new_length;
	char	*updated_buff;
	char	*new_line;

	if (temp_storage == NULL || *temp_storage == '\0')
		return (NULL);
	new_line = ft_strchr(temp_storage, '\n');
	if (new_line == NULL)
	{
		free(temp_storage);
		return (NULL);
	}
	new_length = ft_strlen(new_line + 1);
	updated_buff = malloc(new_length + 1);
	if (updated_buff == NULL)
	{
		free(temp_storage);
		return (NULL);
	}
	ft_memcpy(updated_buff, new_line + 1, new_length);
	updated_buff[new_length] = '\0';
	free(temp_storage);
	return (updated_buff);
}

char	*get_next_line(int fd)
{
	static char	*temp_storage;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	temp_storage = ft_get_whole_line(fd, temp_storage);
	if (temp_storage == NULL)
		return (NULL);
	if (*temp_storage == '\0')
	{
		free(temp_storage);
		temp_storage = NULL;
		return (NULL);
	}
	line = ft_extract_line(temp_storage);
	if (!line)
	{
		free(temp_storage);
		temp_storage = NULL;
		return (NULL);
	}
	temp_storage = ft_renew_buffer(temp_storage);
	return (line);
}
