/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 04:37:16 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/26 04:45:54 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <limits.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif
void *ft_memset(void *b, int c, size_t len);
void ft_bzero(void *s, size_t n);
int includes(char *str, char c);
size_t ft_strlen(const char *str);
char *ft_strdup(const char *s);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);

#endif