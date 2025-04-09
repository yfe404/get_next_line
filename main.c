#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1000

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

int main() {
    char *buffer;
    int fd = open("example.txt", O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

	while(get_next_line(fd, &buffer) == 1)
    	printf("%s\n", buffer);

    close(fd);
    return 0;
}
