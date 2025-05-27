#include <stdlib.h>
#include <string.h>

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


int main()
{
	char *buff;
	char *addme;

	buff = malloc(2);
	addme = malloc(4);

	buff[0] = 'H';
	buff[1] = 'i';

	addme[0] = '\n';
	addme[1] = 'f';
	addme[2] = 'r';
	addme[3] = 'i';

	buff = concat(buff, addme, 2, 4);
	printf("%s\n", buff);
	free(buff);


}
