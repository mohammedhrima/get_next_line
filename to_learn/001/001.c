/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   001.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:21:27 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/20 23:24:30 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

/*char* qra_lfile(char *file)
{
	int			fd;
	static int	var;

	fd = open(file,O_RDWR | O_CREAT);
	if(fd == -1)
		return (NULL);
	
	char* str = (char*)malloc(5*sizeof(char));
	if(!str)
		return (0);
	str[4] = '\0';
	read(fd, str, 4);
	close(fd);
	return (str);
}*/
void	func(void)
{
	static int var = 0;
	
	if (!var)
	{
		printf("I will add one\n");
		var += 1;
	}
	else
	{
		printf("already added one\n");
	}
	printf("%d\n", var);
}

int	main(void)
{
	func();
	func();
	func();
	func();
}
