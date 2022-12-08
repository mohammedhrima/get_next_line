#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <limits.h>
//#include "./Leak_Hunter/leak_hunter.h"
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
	void *tmp;

	if (count && size > SIZE_MAX / count)
		return (NULL);
//	atexit(leak_report);
	tmp = (void *)malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	free(tmp);
	return (arr);
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
	//atexit(leak_report);
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
	//ptr = tmp;
	return (ptr);
}
char *ft_strtrim(char *str, char c)
{
	int x;

	x = includes(str, c);
	if (!x)
		return (str);
	return (str + x);
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
	//atexit(leak_report);
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

char *read_file(int fd)
{
	char *str;
	char *res;
	char *tmp0;
	static char *backup;
	int i;
	int j;
	int size = BUFFER_SIZE;

	res = NULL;
	str = NULL;
	tmp0 = NULL;
	//atexit(leak_report);

	j = 0;
	printf("\n\n===============START===============\n");
	i = includes(backup, '\n');
	if (i >= 0)
	{
		printf("there is backup with new line: %s\n", backup);
		tmp0 = ft_substr(backup, 0, i ); // extract string from backup till \n
		res = tmp0;
		free(tmp0);
		backup = ft_strtrim(backup, '\n');
		backup++;
		return (res);
	}
	printf("after 1st statement:\nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);

	res = ft_strjoin(backup, res);
	printf("after 2nd statement:\nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	i = 1;
	while (i && includes(str, '\n') == -1)
	{
		tmp0 = (char *)malloc(10000*sizeof(char));
		i = read(fd, tmp0 + j, size);
		str = tmp0;
		free(tmp0);
		j += i;
		size += i;
		str[j] = '\0';
	}
	printf("after 1st while loop:\nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	i = includes(str, '\n');
	char *tmp1 = ft_substr(str, 0,i );
	res = ft_strjoin(res,tmp1 );
	backup = ft_strchr(str, '\n');
	printf("Before returning:\nres: %s\nstr: %s\nbackup: %s\n\n", res, str, backup);
	str = NULL;
//	free(str);
	return (res);
}


int main(int argc, char **argv)
{
	/*while (1)
	{
		char *s = read_file(0);
		red();
		printf("%s", s);
		reset();
	}*/
	//atexit(leak_report);
	int fd1 = open("test.txt", O_RDWR, 0777);

	if (fd1 == -1)
	{
		printf("error reading file\n");
		return (0);
	}
	char *res="abc";
	while (ft_strlen(res))
	{
		res = NULL;
		res = read_file(fd1);
		printf("\033[1;31mthe Return ->%s\n\n\033[0m",res);
	}
	free(res);
	res = NULL;
	close(fd1);
}



