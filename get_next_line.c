/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 04:47:04 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/26 05:33:11 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "Leak_Hunter/leak_hunter.h"



char* there_is_not_new_line_in_backup(char* backup, int i)
{
	char *res;
	char *tmp;
	
	res = ft_substr(backup, 0, i);
	tmp = ft_strdup(backup + i + 1);
	free(backup);
	backup = tmp;
	return(res);
}

char *get_next_line(int fd)
{
	char *res;
	char *str;
	char *tmp;
	static char *backup;
	int i;
	int readen_size;
	int j;
	int size;

	j = 0;
	readen_size = 1;
	size = 0;
	res = NULL;
	tmp = NULL;
	if (fd >= 0)
	{
		str = (char *)malloc(10000 * sizeof(char));
		ft_bzero(str, 10000);
		i = includes(backup, '\n');
		if (ft_strlen(backup) && i != -1)
		{
			res = ft_substr(backup, 0, i);
			tmp = ft_strdup(backup + i + 1);
			free(backup);
			backup = tmp;
			return(res);
		}
			//return(there_is_not_new_line_in_backup(backup,i));
		while (readen_size && includes(str, '\n') == -1)
		{
			readen_size = read(fd, str + j, BUFFER_SIZE);
			j += readen_size;
			str[j] = '\0';
		}
		if (ft_strlen(backup) && i == -1) // add backup to str
		{
			tmp = ft_strjoin(backup, str);
			free(str);
			str = tmp;
		}
		if (readen_size == 0 && !ft_strlen(str))
		{
			free(backup);
			free(str);
			str = NULL;
			return (NULL);
		}

		i = includes(str, '\n');
		if (i == -1)
			i = ft_strlen(str);
		res = ft_substr(str, 0, i);							// substract from the beginning of str till \n if there is else copy it
		backup = ft_substr(str, i + 1, ft_strlen(str) - 1); // cut form /n till the end
		free(str);
	}

	return (res);
}

int main(void)
{
	//atexit(leak_report);
	int fd = open("test.txt", O_RDWR, 0777);
	if (fd == -1)
	{
		printf("error reading file\n");
		return (0);
	}
	char *res;
	res = get_next_line(fd);
	while (res)
	{
		printf("-> %s\n", res);
		free(res);
		res = get_next_line(fd);
	}
	// while(1);

	return (0);
}