/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:52:20 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/29 00:16:14 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	j = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && *s1)
		str[i++] = *s1++;
	free((void *)(s1 - i));
	while (s2 && *s2)
	{
		str[i++] = *s2++;
		j++;
	}
	free((void *)(s2 - j));
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	char			*s1;
	unsigned int	i;

	if (!s || start >= ft_strlen(s))
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

void	*ft_calloc(size_t count, size_t size)
{
	void			*arr;
	size_t			n;
	unsigned char	*ptr;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	arr = (void *)malloc(count * size);
	if (!arr)
		return (NULL);
	n = count * size;
	ptr = (unsigned char *)arr;
	while (0 < n)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
	return (arr);
}
