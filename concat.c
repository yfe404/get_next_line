#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

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
	free(addme);
	return (newbuff);
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

}
