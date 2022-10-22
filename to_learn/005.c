#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#define buffer_size 20

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 && s2)
		return ((char *)s2);
	if (s1 && !s2)
		return ((char *)s1);
	if (!s1 && !s2)
		return (NULL);
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

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

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

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	arr = (void *)malloc(count * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, count * size);
	return (arr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;

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

char	*ft_strchr(const char *s, int c)
{
	int	i;

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
	return ((char *) NULL);
}

char* read_file(int fd)
{
	char *str;
	char *res;
	char *backup;
	int i = 1;

	if(!ft_strlen(str))
	{
		printf("case 1\n");
		str = (char*)malloc((BUFFER_SIZE + 1)*sizeof(char));
		res = (char*)malloc(sizeof(char));
		*res = '\0';
		if(!str)
			return(NULL);
		*str = '\0';
		while (i)
		{
			i = read(fd, str, BUFFER_SIZE);
			str[i] = '\0';
			res = ft_strjoin(res,str);
			printf("res -> %s\n---------------------------------\n",res);
		}
		backup = str;
		free(str);
	}
	else 
	{
		printf("case 2\n");
		res = backup;
		backup = ft_strchr(backup, '7');
		while (res[i] != '\n' && res[i])
			i++;
		res[i] = '\0';
	}
	return(res);
}

int	main(void)
{
	int fd = open("test.txt", O_RDWR, 0777);
	if(fd == -1)
	{
		printf(" error reading file\n");
		return (0);
	}
	char *res;

	printf("\n--------IN MAIN--------\n");
	res = read_file(fd);
	printf("->%s\n\n",res);
	res = read_file(fd);
	printf("->%s\n\n",res);
	/*res = read_file(fd);
	printf("->%s\n\n",res);*/
	//res = read_file(fd);
	//printf("->%s\n",res);

	close(fd);
}
