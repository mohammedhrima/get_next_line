#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#define BUFFER_SIZE 20

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
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	j;

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

char* read_file(int fd)
{
	// printf("196\n");
	char *str;
	char *res;
	static char *backup;
	int i = 1;
	int j = 0;

	str = (char*)malloc((BUFFER_SIZE + 1)*sizeof(char));
	res = (char*)malloc(sizeof(char));
	
	*str = '\0';
	*res = '\0';
	//res = (char*)malloc(sizeof(char));
	/*if(!str)
		return(NULL);*/
	//*res = '\0';
	// printf("207\n");
	printf("\n\n============Start============\nbefore 1st loop: \nres: %s\nstr: %s\nbackup: %s\n\n",res,str,backup);
	
	//str = (char*)malloc((buffer_size + 1)*sizeof(char));
	while (i && !includes(str, '\n'))
	{
		printf("1. -> %s\n",str);
		i = read(fd, str + j, BUFFER_SIZE);
		j += i;
		str[j] = '\0';
		printf("2. -> %s\n\n",str);
		//str+=BUFFER_SIZE;
	}
	printf("after first loop:\nres: %s\nstr: %s\nbackup: %s\n\n",res,str,backup);
	if(ft_strlen(backup))
	{
		if(includes(backup,'\n'))
		{
			printf("there is new line in backup\n\n");
			res = backup;
			int i = 0;
			while (*backup != '\n')
			{
				backup++;
				i++;
			}
			res = ft_substr(res,0,i);
			return (res);
		}
		printf("there is backup -> %s\n",backup);
		res = backup;
		printf("check res -> %s\n\n",res);
		backup = NULL;
	}
	printf("after 1st statement: \nres: %s\nstr: %s\nbackup: %s\n\n",res,str,backup);
	
	
	res = ft_strjoin(res, str);
	//res = ft_strjoin(backup,res);
	printf("after 1st loop: \nres: %s\nstr: %s\nbackup: %s\n\n",res,str,backup);

	if(includes(str,'\n'))
	{
		int i = 0;
		while (str[i] != '\n')
			i++;
		backup = ft_strdup(ft_strchr(str, '\n'));
		printf("-> backup in if statement: %s\n\n",backup);
		i = 0;
		while (res[i] != '\n')
			i++;
		if(res[i])
			res = ft_substr(res,0,i);
		free(str);
		//str = NULL;
	}
	printf("after 2nd if statement: \nres: %s\nstr: %s\nbackup: %s\n\n",res,str,backup);
		
		/*
		j = includes(str,'7');
		if(j)
		{
			backup = (char*)malloc((buffer_size + 1)*sizeof(char));
			ft_bzero(backup,j);
			backup = ft_substr(str,j,ft_strlen(str)-j);
			res = ft_strchr(str,'7');
		}
	
	else
	{
		printf("case 2\n");
		backup = ft_strchr(str, '\n');
		int i = 0;
		while (str[i] != '\n')
			i++;
		res =(char*)malloc((i+1)*sizeof(char));
		if(!res)
			return (NULL);
		*res = '\0';
		ft_strlcpy(res,str,i);
		str += i;
		printf("after else: \nres: %s\nstr: %s\nbackup: %s\n\n",res,str,backup);

	}*/
	str = NULL;
	free(str);
	printf("before return: \nres: %s\nstr: %s\nbackup: %s\n\n",res,str,backup);
	

	/*else
	{
		res = ft_trim(&backup,'\n');
	}*/
	
	
	return(res);
}

int	main(void)
{
	/*while (1)
	{
		char *s = read_file(0);
		printf("%s\n", s);
	}*/
	int fd = open("test.txt", O_RDWR|O_CREAT, 0777);
	if(fd == -1)
	{
		printf(" error reading file\n");
		return (0);
	}
	char *res1,*res2,*res3,*res4, *res5;

	res1 = read_file(fd);
	res2 = read_file(fd);
	res3 = read_file(fd);
	res4 = read_file(fd);
	res5 = read_file(fd);
	printf("\n--------IN MAIN--------\n");
	printf("the Return ->%s\n\n",res1);
	printf("the Return ->%s\n\n",res2);
	printf("the Return ->%s\n\n",res3);
	printf("the Return ->%s\n\n",res4);
	printf("the Return ->%s\n\n",res5);
	
	/*res = read_file(fd);
	printf("->%s\n\n",res);*/
	//res = read_file(fd);
	//printf("->%s\n",res);

	close(fd);
}
