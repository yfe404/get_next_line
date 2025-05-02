#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*get_next_line(const int fd)
{
	int 	count;
	int		bytes_read;
	char	*line;
	char 	c;

	if (fd < 0)
		return NULL;
	count = 0;
	c = '\0';
	line = malloc(BUFF_SIZE);
	bytes_read = read(fd, &c, 1);
	if (bytes_read <= 0)
	{
		free(line);
		return NULL;
	}
	while (bytes_read >= 0)
	{
		if (c == '\n' || bytes_read == 0) 
		{
			line[count++] = '\n';
			line[count] = '\0';
			return line;
		}
		line[count++] = c;
		bytes_read = read(fd, &c, 1);

		if (count >= BUFF_SIZE)
		{
			free (line);
			return NULL;
		}
	}
	free(line);
	return NULL;
}


