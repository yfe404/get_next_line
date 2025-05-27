/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfeunteu <yfeunteu@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:02:15 by yfeunteu          #+#    #+#             */
/*   Updated: 2025/05/20 17:08:30 by yfeunteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int	check_free(int cond, void *ptr)
{
	if (cond)
		free(ptr);
	return (cond);
}

char	*get_next_line(const int fd)
{
	int		count;
	int		bytes_read;
	char	*line;
	char	c;

	if (fd < 0)
		return (NULL);
	count = 0;
	c = '\0';
	line = malloc(BUFF_SIZE);
	bytes_read = read(fd, &c, 1);
	if (check_free(bytes_read <= 0, line))
		return (NULL);
	while (bytes_read >= 0)
	{
		if (c == '\n' || bytes_read == 0)
		{
			if (bytes_read)
				line[count++] = '\n';
			line[count] = '\0';
			return (line);
		}
		line[count++] = c;
		bytes_read = read(fd, &c, 1);
		if (check_free(count >= BUFF_SIZE, line))
			return (NULL);
	}
	free(line);
	return (NULL);
}
