/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:14:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/01/21 16:54:49 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*dst;
	size_t	file_len;
	size_t	i;
	size_t	x;
	size_t	count;

	i = 0;
	count = 0;
	while (file_len != 0)
	{
		file_len = read(fd, buf, BUFFER_SIZE);
		count += file_len;
	}
	//while (buf[i - 1] != '\n' && buf[i] != '\0' && i < count)
	//	i++;
	printf("%zu", count);

	dst = (char *) malloc (count + 1);
	if (!dst)
	return (NULL);
	x = 0;
	while (i--)
	{
		dst[x] = buf[x];
		x++;
	}
	dst[x] = '\0';
	printf("%s", dst);
	return (dst);
}


int main()
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}
