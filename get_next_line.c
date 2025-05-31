/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfeunteu <yfeunteu@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:08:03 by yfeunteu          #+#    #+#             */
/*   Updated: 2025/05/31 09:31:42 by yfeunteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "get_next_line.h"

int		has_next_line(t_buffer *buffer);
char	*extract_line(char *buff, char **next_line, int s_buff, int pos);
char	*concat(char *buff, char *addme, size_t s_buff, size_t s_addme);
int		read_next(int fd, t_buffer *b, char **new_line);

char	*get_next_line(int fd)
{
	static t_buffer	b[MAX_FD] = {0};
	char			*new_line;
	int				nl_pos;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	nl_pos = -1;
	while (1)
	{
		nl_pos = has_next_line(&b[fd]);
		new_line = NULL;
		if (nl_pos >= 0)
		{
			b[fd].dat = extract_line(b[fd].dat, &new_line, b[fd].s_dat, nl_pos);
			b[fd].s_dat -= nl_pos + 1;
			break ;
		}
		if (!read_next(fd, &b[fd], &new_line))
			break ;
	}
	return (new_line);
}
