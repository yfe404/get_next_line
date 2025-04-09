#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

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
