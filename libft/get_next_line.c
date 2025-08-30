/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:46:12 by amairia           #+#    #+#             */
/*   Updated: 2025/07/27 22:46:13 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// delete line find
static char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i] || (buffer[i] == '\n' && !buffer[i + 1]))
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

// take line for return
static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_file(int fd, char *buffer)
{
	char	*tmp;
	int		read_tst;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	read_tst = 1;
	while (read_tst > 0)
	{
		read_tst = read(fd, tmp, BUFFER_SIZE);
		if (read_tst <= -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		tmp[read_tst] = 0;
		buffer = ft_strjoin_free(buffer, tmp);
		if (!buffer || ft_strchr(tmp, '\n'))
			break ;
	}
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*res;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
	{
		if (buffer[fd])
			free(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	res = ft_line(buffer[fd]);
	buffer[fd] = ft_next(buffer[fd]);
	return (res);
}
