#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define buffer_size 3
#include <string.h>


char *concat_till_newline(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(dest[j])
		j++;
	while(src[i] && src[i] != '\n')
	{
		dest[j] = src[i];
		printf("line 21 %c\n",dest[j]);
		i++;
		j++;
	}
	dest[j] = '\0';
	if(src[i] == '\n')
	{
		i++;
		j = i;
		while(src[j])
			j++;
		src[j] = '\0';
		printf("line 33 %s\n",&(src[i]));
		return(&(src[i]));
	}
	return(NULL);
}

char* read_file(int fd)
{

	int size = BUFFER_SIZE;
	char* str = (char*)malloc((size + 1)*sizeof(char));
	char *res = (char*)malloc((200)*sizeof(char));
	char *backup = (char*)malloc((size + 1)*sizeof(char));

	if(!str)
		return (0);
	
	*backup = '\0';
	*res = '\0';
	*str = '\0';

	int j = 0;
	
	while (j < 60)
	{
		read(fd, str, 3);
		str[3] = '\0';
		if(backup)
		{
			strcat(backup,str);
			str = backup;
			printf("line 64 %s\n",str);
			backup = (char*)malloc((size + 1)*sizeof(char));
			*backup = '\0';
		}
		backup = concat_till_newline(res,str);
		printf("line 69 %s\n",backup);
		*str = '\0';
		printf("line 71 %s\n",res);
		j++;
		size *= 2;
	}
	//free(res);
	return (res);
}

int	main(void)
{
	int fd = open("file.txt",O_RDWR | O_CREAT);
	if(fd == -1)
		return (0);

	char *res = read_file(fd);
	printf("-> %s\n",res);
	close(fd);
}