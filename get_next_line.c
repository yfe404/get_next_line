#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef BUFF_SIZE
#define BUFF_SIZE 10
#endif

int	ft_strcmp(const char *s1, const char *s2)
{
	while(s1 && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return *s1 - *s2;	
}


char *concat(char *buff, char *addme, size_t s_buff, size_t s_addme)
{
	char	*newbuff;	
	int		offset;

	offset = s_buff;
	newbuff = malloc(s_buff + s_addme);
	if (!newbuff)
		return (NULL);
	while(s_buff--)
		newbuff[s_buff] = buff[s_buff];
	while(s_addme--)
		newbuff[offset + s_addme] = addme[s_addme];
	free(buff);
	//free(addme);
	return (newbuff);
}

typedef struct s_buffer {
	int		s_dat;
	char	*dat;
} t_buffer;

int	has_next_line(t_buffer *buffer)
{
	int pos;

	pos = 0;
	while(pos < buffer->s_dat)
		if (buffer->dat[pos++] == '\n')
			return (pos-1);
	return (-1);
}

char * extract_line(char *buff, char **next_line, int s_buff, int pos)
{
	int tmp;
	char	*newbuff;

	tmp = 0;
	*next_line = malloc(pos + 2);
	newbuff = malloc(s_buff - pos);
	while(tmp <= pos)
	{
		(*next_line)[tmp] = buff[tmp];
		tmp++;
	}
	(*next_line)[tmp] = '\0';
	while (tmp < s_buff)
	{
		newbuff[tmp - pos - 1] = buff[tmp];
		tmp++;
	}
	free(buff);
	return newbuff;
}


char	*get_next_line(int fd)
{
	static	t_buffer buffer = {0, NULL};
	char	*new_line;
	char	*tmp;
	int		bytes_read;
	int		nl_pos;

	nl_pos = -1;
	tmp = malloc(BUFF_SIZE);

	while (1) 
	{
		bytes_read = read(fd, tmp, BUFF_SIZE);

		if (bytes_read < 0 || (bytes_read == 0 && buffer.s_dat == 0) || !tmp)
		{
			free(tmp);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			buffer.dat = extract_line(buffer.dat, &new_line, buffer.s_dat, buffer.s_dat);
			buffer.s_dat = 0;
			free(buffer.dat); // can be done in extract
			return buffer.dat;
		}
		buffer.dat = concat(buffer.dat, tmp, buffer.s_dat, bytes_read);
		buffer.s_dat = buffer.s_dat + bytes_read;
		nl_pos = has_next_line(&buffer);
		if (nl_pos >= 0)
		{
			buffer.dat = extract_line(buffer.dat, &new_line, buffer.s_dat, nl_pos);
			buffer.s_dat -= nl_pos + 1;
			return new_line;
		}
	}
}

/*
int main()
{
	char *buff;
	char *addme;
	char *next_line;

	buff = malloc(2);
	addme = malloc(4);

	buff[0] = 'H';
	buff[1] = 'i';

	addme[0] = '\n';
	addme[1] = 'f';
	addme[2] = 'r';
	addme[3] = 'i';

	buff = concat(buff, addme, 2, 4);
	printf("Buffer after concat: %s\n", buff);

	buff = extract_line(buff, &next_line, 6, 2);
	printf("Next line: %s\n", next_line);
	printf("Remaining buffer: ");
	fflush(stdout);
	write(STDOUT_FILENO, buff, 3);

	free(buff);
}*/
/*
int main() {
    char *buffer;
    int fd = open("example.txt", O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

	while(buffer = get_next_line(fd))
	{
    	printf("%s", buffer);
	}

    close(fd);
    return 0;
}
*/
