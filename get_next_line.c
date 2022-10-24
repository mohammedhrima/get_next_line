/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:37:49 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/23 23:55:58 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_if_new_line_in_backup(char **res, char **backup, int *i)
{
	*res = ft_substr(*backup, 0, *i);
	*backup = ft_strtrim(*backup, '\n');
	(*backup)++;
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

char	*get_next_line(int fd)
{
	char		*str;
	char		*res;
	static char	*backup;
	int			i;

	res = NULL;
	str = (char *)malloc((1000000) * sizeof(char));
	*str = '\0';
	i = includes(backup, '\n');
	if (i >= 0)
		return (ft_if_new_line_in_backup(&res, &backup, &i));
	res = ft_strjoin(backup, res);
	if (!ft_while_loop(&str, &fd))
		return (NULL);
	res = ft_strjoin(res, ft_substr(str, 0, includes(str, '\n')));
	backup = ft_strchr(str, '\n');
	str = NULL;
	free(str);
	return (res);
}
