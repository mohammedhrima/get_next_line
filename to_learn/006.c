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

char	*ft_strrchr(const char *s, int c)
{
	int	len;

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

int	includes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i] == c)
			return (i);
		i++;
	}
	return(0);
}

char *ft_trim(char **str, char c)
{
	int i;
	int j = 0;
	char *res;

	while (**str && **str != c)
	{
		(*str)++;
		i++;
	}
	res = (char*)malloc((i)*sizeof(char));
	if(!res)
		return (NULL);
	res[i] = '\0';
	while (i > 0)
	{
		res[i] = *(*str - j);
		i--;
		j++;
	}
	return(res);
}

char* read_file(int fd)
{
	char *str;
	char *res;
	char *backup;
	int i = 1;
	int j = 0;

	str = (char*)malloc((BUFFER_SIZE + 1)*sizeof(char));
	res = (char*)malloc(sizeof(char));
	if(!str || !str)
		return(NULL);
	*res = '\0';
	*str = '\0';

	if(!ft_strlen(backup))
	{
		
		i = read(fd, str, BUFFER_SIZE);
		str[i] = '\0';
		j = includes(str,'7');
		if(j)
		{
			backup = (char*)malloc((BUFFER_SIZE + 1)*sizeof(char));
			ft_bzero(backup,j);
			backup = ft_substr(str,j,ft_strlen(str)-j);
			res = ft_strchr(str,'7');
		}
	}
	else
	{
		res = ft_trim(&backup,'\n');
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
	/*res = read_file(fd);
	printf("->%s\n\n",res);*/
	/*res = read_file(fd);
	printf("->%s\n\n",res);*/
	//res = read_file(fd);
	//printf("->%s\n",res);

	close(fd);
}
