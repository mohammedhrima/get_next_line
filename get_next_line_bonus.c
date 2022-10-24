/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:37:53 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/24 02:50:59 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

char	*ft_if_new_line_in_backup(char **res, char **backup[2000], int *i,int *fd)
{
		*res = ft_substr((*backup)[*fd], 0, *i);
		(*backup)[*fd] = ft_strtrim((*backup)[*fd], '\n');
		(*backup)[*fd]++;
		return (*res);
}

char	*ft_while_loop(char **str, int *fd)
{
	int	i;
	int	j;
	int	size;

	size = BUFFER_SIZE;
	i = 1;
	j = 0;
	while (i && includes(*str, '\n') == -1)
	{
		i = read(*fd, (*str) + j, size);
		if (i < 0)
		{
			free(*str);
			return (NULL);
		}
		j += i;
		size += i;
		(*str)[j] = '\0';
	}
	return ("");
}

char	*get_next_line_bonus(int fd)
{
	char		*str;
	char		*res;
	static char	*backup[OPEN_MAX];
	int			i;
	res = NULL;
	//str = (char *)malloc((1000000) * sizeof(char));
	*str = '\0';
	i = includes(backup[fd], '\n');
	if (i >= 0)
		return (ft_if_new_line_in_backup(&res, &backup, &i, &fd));
	res = ft_strjoin(backup[fd], res);
	if (!ft_while_loop(&str, &fd))
		return (NULL);
	res = ft_strjoin(res, ft_substr(str, 0, includes(str, '\n')));
	backup[fd] = ft_strchr(str, '\n');
	str = NULL;
	free(str);
	return (res);
}
5 
hgfjsghjgfshjgsdhjfgsdgdsjhsjsdgjf\n
str = dgdgd 
str = ft_strjoin(str, byn)