#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	int count;
	char c;

	*line = malloc(BUFF_SIZE);

	count = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n') 
		{
			(*line)[count] = '\0';
			return 1;
		}
		(*line)[count++] = c;
		
		if (count >= BUFF_SIZE)
			return -1;
	}
	return 0;
}


