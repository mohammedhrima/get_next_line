#include "get_next_line_bonus.h"
#include <stdio.h>

char *get_next_line_bonus(int fd);
int main(void)
{
	//test get_next_line_bonus
	int fd1 = open("test0.txt", O_RDWR, 0777);
	int fd2 = open("test1.txt", O_RDWR, 0777);
	int fd3 = open("test2.txt", O_RDWR, 0777);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("error reading file\n");
		return (0);
	}
	char *res;
	res = "abc";

	while (ft_strlen(res))
	{
		res = get_next_line_bonus(fd1);
		printf("\033[1;31mthe Return ->%s\n\n\033[0m",res);
		res = get_next_line_bonus(fd2);
		printf("\033[1;32mthe Return ->%s\n\n\033[0m",res);
		res = get_next_line_bonus(fd3);
		printf("\033[1;33mthe Return ->%s\n\n\033[0m",res);
	}
	free(res);
	res = NULL;
	close(fd1);
	close(fd2);
	close(fd3);
}