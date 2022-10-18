#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

/*char* qra_lfile(char *file)
{
	int fd = open(file,O_RDWR | O_CREAT);
	if(fd == -1)
		return (NULL);
	
	char* str = (char*)malloc(5*sizeof(char));
	if(!str)
		return (0);
	str[4] = '\0';
	read(fd, str, 4);
	close(fd);
	return (str);
}*/
void func(void)
{
	static int i = 0;
	i+=1;
	printf("%d\n",i);
}

int	main(void)
{
	//char *data = qra_lfile("file.txt");
	//printf("->%s\n", data);
	//int n = func();
	func();
	func();
	//printf("-> %d\n",func());

}