#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
char *ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	int i;
	int j;

	i = 0;
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
char *ft_strdup(const char *s)
{
	char *ptr;
	int i;

	ptr = (char *)malloc(ft_strlen(s) + 1);
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
char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *ptr;
	unsigned int i;

	if (!s)
		return (ft_strdup(""));
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(len * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char *ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (char)c)
		{
			while (s[i] == (char)c)
				i++;
			return ((char *)(s + i));
		}
		i++;
	}
	if (c == 0 && s[i] == 0)
		return ((char *)(s + i));
	return ((char *)NULL);
}
char *ft_strrchr(const char *s, int c)
{
	int len;

	len = ft_strlen(s);
	s += len;
	if (c == 0)
		return ((char *)s);
	while (len >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		len--;
	}
	return (NULL);
}
int includes(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		//printf("%d -> %c\n",i,str[i]);
		if (str[i] == c)
		{
			printf("%c is found\n",c);
			return (1);
		}
		i++;
	}
	return (0);
}
char *ft_trim(char **str, char c)
{
	int i = 0;
	int j = 0;
	char *res;

	while (**str && **str != c)
	{
		(*str)++;
		i++;
	}
	res = (char *)malloc((i) * sizeof(char));
	if (!res)
		return (NULL);
	res[i] = '\0';
	while (i > 0)
	{
		res[i] = *(*str - j);
		i--;
		j++;
	}
	return (res);
}
size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int j;

	j = 0;
	if (!size)
		return (ft_strlen(src));
	while (j < size - 1 && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (ft_strlen(src));
}

char *read_file(int fd)
{
	char *str;
	char *res;
	static char *backup;
	int i = 1;
	int j = 0;

	str = (char *)malloc((1000000) * sizeof(char));
	res = (char *)malloc(sizeof(char));
	*str = '\0';
	*res = '\0';

	printf("\n\n============Start============\nbefore 1st loop: \nres: %s\nstr: %s\n", res, str);

	if (ft_strlen(backup) && includes(backup, '\n'))
	{
		printf("backup(with new line): %s\n", backup);
		res = backup;
		int i = 0;
		while (backup[i] != '\n')
			i++;
		res = ft_substr(res, 0, i+1);
		backup += i ;
		//printf("before 1st return: \nres: %s\nbackup: %s\n", res, backup);
		return (res);
	}
	printf("\n");

	while (i && !includes(str, '\n'))
	{
		//printf("1. -> %s\n",str);
		i = read(fd, str + j, BUFFER_SIZE);
		j += i;
		str[j] = '\0';
		//printf("2. -> %s\n\n",str);
		//str+=BUFFER_SIZE;
	}
	printf("after first loop:\nres: %s\nstr: %s\nbackup: %s\n\n", res,str, backup);
	if (ft_strlen(backup))
	{
		printf("backup(without new line): %s\n", backup);
		//printf("there is backup -> %s\n", backup);
		str = ft_strjoin(backup,str);
		printf("check res -> %s\n\n", str);
		backup = NULL;
	}
	printf("after 1st statement: \nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	i = 0;
	while (str && str[i] && str[i] != '\0')
	{
		if(str[i] == '\n')
			break;
		i++;
	}
	
	res = ft_substr(str, 0,i);
	str += i;
	
	printf("after joining: \nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	if(ft_strlen(str))
	{
		printf("set backup");
		backup = ft_strdup(str);
	}
	/*if (includes(str, '\n'))
	{
		int i = 0;
		while (str[i] != '\n')
			i++;
		backup = ft_strdup(str + i + 1);
		//printf("-> backup in if statement: %s\n\n", backup);
		i = 0;
		while (res[i] != '\n')
			i++;
		res[i] = 0;
		//free(str);
		printf("after 2nd statement: \nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	}*/
	free(backup);
	str= NULL;
	//printf("after 2nd if statement: \nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	printf("before return: \nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	return (res);
}

void red()
{
	printf("\033[1;33m");
}
void reset()
{
	printf("\033[0m");
}

int main(void)
{
	int fd = open("test.txt", O_RDWR, 0777);
	if (fd == -1)
	{
		printf(" error reading file\n");
		return (0);
	}

	//printf("\n--------IN MAIN--------\n");
	char *res = read_file(fd);
	red();
	printf("the Return ->%s\n\n",res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();
	res = read_file(fd);
	red();
	printf("the Return ->%s\n\n", res);
	reset();

	close(fd);
}
