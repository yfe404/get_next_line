/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfeunteu <yfeunteu@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 08:57:02 by yfeunteu          #+#    #+#             */
/*   Updated: 2025/05/31 08:57:04 by yfeunteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*concat(char *buff, char *addme, size_t s_buff, size_t s_addme)
{
	char	*newbuff;	
	int		offset;

	offset = s_buff;
	newbuff = malloc(s_buff + s_addme);
	if (!newbuff)
		return (NULL);
	while (s_buff--)
		newbuff[s_buff] = buff[s_buff];
	while (s_addme--)
		newbuff[offset + s_addme] = addme[s_addme];
	free(buff);
	return (newbuff);
}

int	has_next_line(t_buffer *buffer)
{
	int	pos;

	pos = 0;
	while (pos < buffer->s_dat)
		if (buffer->dat[pos++] == '\n')
			return (pos - 1);
	return (-1);
}

char	*update_buffer(char *buff, int s_buff, int pos)
{
	char	*newbuff;
	int		it1;
	int		it2;

	it1 = 0;
	it2 = pos + 1;
	newbuff = malloc(s_buff - pos - 1);
	if (!newbuff)
		return (NULL);
	while (it2 < s_buff)
		newbuff[it1++] = buff[it2++];
	free(buff);
	return (newbuff);
}

char	*extract_line(char *buff, char **next_line, int s_buff, int pos)
{
	int		i;
	char	*newbuff;

	i = 0;
	if (!buff || !next_line || pos >= s_buff)
		return (NULL);
	*next_line = malloc(pos + 2);
	if (!(*next_line))
		return (NULL);
	while (i <= pos)
	{
		(*next_line)[i] = buff[i];
		i++;
	}
	(*next_line)[i] = '\0';
	if (s_buff - pos - 1 <= 0)
	{
		free(buff);
		return (NULL);
	}
	newbuff = update_buffer(buff, s_buff, pos);
	if (!newbuff)
		free(*next_line);
	return (newbuff);
}

int	read_next(int fd, t_buffer *b, char **new_line)
{
	char	*tmp;
	int		bytes_read;

	tmp = malloc(BUFFER_SIZE);
	bytes_read = read(fd, tmp, BUFFER_SIZE);
	if (bytes_read < 0 || (bytes_read == 0 && b->s_dat == 0) || !tmp)
	{
		b->s_dat = 0;
		free(tmp);
		return (0);
	}
	else if (bytes_read == 0)
	{
		b->dat = extract_line(b->dat, new_line, b->s_dat, b->s_dat - 1);
		b->s_dat = 0;
		free(tmp);
		return (0);
	}
	b->dat = concat(b->dat, tmp, b->s_dat, bytes_read);
	b->s_dat = b->s_dat + bytes_read;
	free(tmp);
	return (1);
}
