#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define buffer_size 3
#include <string.h>

ssize_t read(int fd, void *buf, size_t count);
{
	
}

int	main(void)
{
	int fd = open("file.txt",O_RDWR | O_CREAT);
	if(fd == -1)
		return (0);
	char *data = read_file(fd);
}