#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd);
int main(void)
{
	//test get_next_line
	//for fd = 0;
	/*while (1)
	{
		char *s = get_next_line(0);
		printf("\033[1;33mthe Return ->%s\n\n\033[0m", s);
	}*/
	int fd = open("test.txt", O_RDWR, 0777);
	if (fd == -1)
	{
		printf(" error reading file\n");
		return (0);
	}
	char *res;
	res = NULL;
	int i = 0;
	while (i < 10)
	{
		res = get_next_line(fd);
		printf("\033[1;33mthe Return ->%s\n\n\033[0m",res);
		i++;
	}
	free(res);
	res = NULL;
	close(fd);
}