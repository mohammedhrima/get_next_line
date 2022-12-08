#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <limits.h>
//#include "Leak_Hunter/leak_hunter.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

void *ft_memset(void *b, int c, size_t len)
{
	size_t i;
	unsigned char *ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*ptr = c;
		ptr++;
		i++;
	}
	return (b);
}

void ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void *ft_calloc(size_t count, size_t size)
{
	void *arr;

	if (count && size > SIZE_MAX / count)
		return (NULL);

	arr = (void *)malloc(count * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, count * size);
	return (arr);
}

int includes(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
	char *ptr;
	int i;

	ptr = (char *)malloc((ft_strlen(s) + 1)*sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *ptr;
	char *s1;
	unsigned int i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(len * (sizeof(char) + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	s1 = ft_strdup(s);
	while (i < len && s[start])
	{
		ptr[i] = s1[start];
		start++;
		i++;
	}
	free(s1);
	ptr[i] = '\0';
	return (ptr);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	int i;
	int j;

	i = 0;
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	// atexit(leak_report);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t j;
	size_t len;

	j = 0;
	if (!size || size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	len = ft_strlen(dst);
	while (j < size - len - 1 && src[j] != '\0')
	{
		dst[len + j] = src[j];
		j++;
	}
	dst[len + j] = '\0';
	return (ft_strlen(src) + len);
}

void red()
{
	printf("\033[1;31m");
}

void green()
{
	printf("\033[1;32m");
}

void blue()
{
	printf("\033[0;34m");
}

void reset()
{
	printf("\033[0m");
}

void yellow()
{
	printf("\033[0;33m");
}



char *get_next_line(int fd)
{
	char *res;
	char *str;
	char 	*tmp;
	char	*tmp2;
	static char *backup;
	int i;
	int readern_size;
	static int j;
	int size;

	j = 0;
	readern_size = 1;
	size = 0;
	res = NULL;

	size = 0;
	tmp = NULL;
	//tmp = NULL;
	// tmp = NULL;
	str = (char *)malloc(10000 * sizeof(char));
	ft_bzero(str, 10000);

	
	//printf("\n\n===============START===============\nres: %s\nstr: %s\nbackup: %s\ntmp: %s\n\n", res, str, backup, tmp);
	i = includes(backup, '\n');
	if (ft_strlen(backup) && i != -1)
	{
		green();
	//	printf("there is backup with new line: %s ", backup);
		reset();
	//	printf("\n");
		res = ft_substr(backup, 0, i);
		tmp = ft_strdup(backup + i + 1);
		printf("%p : %s\n", tmp, tmp);
		free(backup);
		backup = tmp;
		return (res);
	}
	//printf("after if statement 1:\nres: %s\nstr: %s\nbackup: %s\ntmp: %s\n\n", res, str, backup, tmp);

	while (readern_size && includes(str, '\n') == -1)
	{
		readern_size = read(fd, str + j, BUFFER_SIZE);
		j += readern_size;
		str[j] = '\0';
		// printf("reading to str -> %s\n",str);
	}

	//printf("after while loop 1:\nres: %s\nstr: %s\nbackup: %s\ntmp: %s\n\n", res, str, backup, tmp);
	//add back to str
	if (ft_strlen(backup) && i == -1)
	{
		green();
		//printf("there is back up without new line: %s\n",backup);
		reset();
		tmp = ft_strjoin(backup, str);
		free(str);
		str = tmp;
	}
	//printf("after if statement 2:\nres: %s\nstr: %s\nbackup: %s\ntmp: %s\n\n", res, str, backup, tmp);

	if (readern_size == 0 && !ft_strlen(str))
	{
		//printf("\n\n==========I AM IN THE END==========\n\n");
		free(backup);
		free(str);
		str = NULL;
		return (NULL);
	}

	i = includes(str, '\n');
	if (i == -1)
		i = ft_strlen(str);
	res = ft_substr(str, 0, i);					  // substract from the beginning of str till \n if there is else copy it
	backup = ft_substr(str, i + 1, ft_strlen(str) - 1); // cut form /n till the end
	free(str);
	

	return (res);
}

int main(void)
{
	//atexit(leak_report);
	int fd = open("test.txt", O_RDWR, 0777);
	if (fd == -1)
	{
		printf("error reading file\n");
		return (0);
	}
	char *res;
/*	while (1)
	{
		res = get_next_line(0);
		yellow();
		printf("-> %s\n",res);
		reset();
	}*/
	res = get_next_line(fd);
	while (res)
	{
		printf("-> %s\n", res);
		free(res);
		res = get_next_line(fd);
	}
	//while(1);

	return (0);
}