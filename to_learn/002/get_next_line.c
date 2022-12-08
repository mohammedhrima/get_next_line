/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:52:22 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/29 01:32:05 by mhrima           ###   ########.fr       */
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

void	handle_backup_and_set_res(char **backup, char **str, char **res)
{
	int		i;
	char	*tmp;

	if (ft_strlen(*backup))
	{
		tmp = ft_strjoin(*backup, *str);
		*str = tmp;
		*backup = NULL;
	}
	i = includes(*str, '\n');
	if (i == -1)
	{
		i = ft_strlen(*str) - 1;
		free(*backup);
		*backup = NULL;
	}
	*backup = ft_substr(*str, i + 1, ft_strlen(*str));
	*res = ft_substr(*str, 0, i + 1);
	free(*str);
	*str = NULL;
}

int	read_from_file_and_feed_str(char **str, int fd, int *r)
{
	char	*tmp;

	tmp = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (tmp == NULL)
	{
		free(*str);
		return (0);
	}
	*r = read(fd, tmp, BUFFER_SIZE);
	if (*r == -1)
	{
		free(tmp);
		free(*str);
		return (0);
	}
	tmp[*r] = '\0';
	*str = ft_strjoin(*str, tmp);
	return (1);
}

void	in_the_end_of_file(char **backup, char **str, char **res)
{
	free(&backup);
	free(&str);
	free(&res);
}

char	*get_next_line(int fd)
{
	char		*res;
	char		*str;
	static char	*backup;
	int			r;

	res = NULL;
	if (fd < 0)
		return (NULL);
	str = (char *)ft_calloc(1, sizeof(char));
	r = 1;
	while (r && includes(str, '\n') == -1)
	{
		if (!r)
		{
			in_the_end_of_file(&backup, &str, &res);
			return (NULL);
		}
		if (!read_from_file_and_feed_str(&str, fd, &r))
			return (NULL);
	}
	handle_backup_and_set_res(&backup, &str, &res);
	return (res);
}
