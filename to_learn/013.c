#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>

int main(void)
{
	int fd;
	fd = open("test.txt", O_RDWR, 0777);
	printf("%d\n",fd);
	fd = open("test1.txt", O_RDWR, 0777);
	printf("%d\n",fd);
	fd = open("test2.txt", O_RDWR, 0777);
	printf("%d\n",fd);
	fd = open("test3.txt", O_RDWR, 0777);
	printf("%d\n",fd);
	close(fd);
}