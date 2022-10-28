/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:52:22 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/28 21:22:06 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	includes(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}


char	*get_next_line(int fd)
{
	char *res;
	char *str;
	char *tmp0;
	char *tmp1;
	static char *backup;
	int r;
	int i;

	res = NULL;
	str = NULL;
	tmp0 = NULL;
	tmp1 = NULL;
	if (fd < 0)
		return (NULL);
	str = (char *)malloc(sizeof(char));
	ft_bzero(str, 1);
	tmp0 = NULL;
	i = includes(backup, '\n');
	if (ft_strlen(backup) && i != -1 && (size_t)i < ft_strlen(backup) - 1)
	{
		res = ft_substr(backup, 0, i + 1);
		tmp1 = ft_substr(backup, i + 1, ft_strlen(backup));
		free(str);
		free(backup);
		backup = ft_strdup(tmp1);
		free(tmp1);
		str = NULL;
		tmp1 = NULL;
		return (res);
	}
	r = 1;
	i = includes(str, '\n');
	while (r && i == -1)
	{
		if (!r)
		{
			free(backup);
			free(str);
			free(res);
			return (NULL);
		}
		tmp0 = (char *)malloc(BUFFER_SIZE * sizeof(char));
		ft_bzero(tmp0, BUFFER_SIZE);
		r = read(fd, tmp0, BUFFER_SIZE);
		if (r == -1)
		{
			free(tmp0);
			free(str);
			return (NULL);
		}
		tmp0[r] = '\0';
		tmp1 = ft_strjoin(str, tmp0);
		free(str);
		free(tmp0);
		str = ft_strdup(tmp1);
		free(tmp1);
		i = includes(str, '\n');
	}
	if (ft_strlen(backup))
	{
		tmp0 = ft_strjoin(backup, str);
		free(backup);
		free(str);
		str = tmp0;
		backup = NULL;
	}
	i = includes(str, '\n');
	if (i == -1)
	{
		i = ft_strlen(str) - 1;
		free(backup);
		backup = NULL;
	}
	backup = ft_substr(str, i + 1, ft_strlen(str));
	res = ft_substr(str, 0, i + 1);
	free(str);
	str = NULL;
	return (res);
}