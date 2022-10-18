#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define buffer_size 3
#include <string.h>

char* read_file(int fd)
{
	char* str = (char*)malloc(5*sizeof(char));
	char *res = str;
	static int size = 0;
	if(!str)
		return (0);
	str[5] = '\0';
	static int j = 0;

	while (1)
	{
		read(fd, str, 1);
		if(*str == '\n')
		{
			read(fd, str, 1);
			//printf("found a new line in %d\n",j);
			res = (char *)malloc((size+1) * sizeof(char));
			strcpy(res, str - j);
			res[j] = 0;
			printf("-> %s\n",res);
			j = 0;
			//free(res);
			break;
		}
		if(*str == '\0')
		{
			printf("\ndoone\n");
			break;
		}
		str++;
		j++;
		size++;
	}
	free(res);
	close(fd);
	return (res);
}



int	main(void)
{
	int fd = open("file.txt",O_RDWR | O_CREAT);
	if(fd == -1)
		return (0);
	char *data = read_file(fd);
	
	//char *data1 = read_file(fd);
	printf("\n---------IN MAIN---------\n%s\n", data/*,data1*/);

}