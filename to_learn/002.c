#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int concat_get_newline_index(char **dst, char const *src)
{
	size_t	j;
	char *res;

	res = (char *)malloc((ft_strlen(*dst) + ft_strlen(src) + 1)*sizeof(char));
	j = 0;
	while (**dst)
	{
		//printf("1");
		res[j] = **dst;
		(*dst)++;
		j++;
	}
	while (*src && *src != '\n')
	{
		//printf("2");
		res[j] = *src;
		src++;
		j++;
	}
	res[j]	 = '\0';
	*dst = res;
	if(*src == '\n')
		return(j);
	return(0);
}

#define buffer_size 3

char* qra_lfile(int fd)
{
	static char *curr;
	static char *new;
	int c;
	static int BUFF;
	int counter = 0;
	new = "\0";
	c = 0;

	/*if(newsize > size)
		size = newsize;*/
	while (counter < 80 )
	{
		curr = NULL;
		if(c)
		{
			printf("-> new line index %d\n",c);
			BUFF = buffer_size + c;
			break;
		}
		else
			BUFF = buffer_size;
		
		curr = (char*)malloc((BUFF + 1)*sizeof(char));
		*curr = 0;
		c = 0;
		if(!curr)
			return (NULL);
		printf("counter :%d  BUff:%d \n",counter,BUFF);
		read(fd, curr,BUFF);
		c = concat_get_newline_index(&new,curr);
		printf("-> %s\n",curr);
		free(curr);
		counter++;
	}
	
	close(fd);
	return (new);
}

int	main(void)
{
	int fd = open("file.txt",O_RDWR | O_CREAT);
	if(fd == -1)
		return (0);
	printf("\n-----Part 1-----\n");
	char *data1 = qra_lfile(fd);
	printf("--->%s\n", data1);
	char *data2 = qra_lfile(fd);
	printf("--->%s\n", data2);

	/*printf("\n-----Part 2-----\n");
	char *data2 = qra_lfile("file.txt");
	printf("--->%s\n", data2);

	printf("\n-----Part 3-----\n");
	char *data3 = qra_lfile("file.txt");
	printf("--->%s\n", data3);

	printf("\n-----Part 4-----\n");
	char *data4 = qra_lfile("file.txt");
	printf("--->%s\n", data4);*/
}