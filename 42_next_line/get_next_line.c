/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:14:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/01/20 18:18:56 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	char	*dst;
	size_t		file_len;
	size_t		i;

//	file_len = ? ;//fino a \n !
	dst = (char *) malloc ((char) buf* sizeof(char));
	if (!dst)
	return (NULL);
	i = 0;
	file_len = read(fd, buf, BUFFER_SIZE);
	while (i < file_len && buf[i] != '\n'&& buf[i] != '\0')
	{
		dst[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		dst[i] = '\n';
	return (dst);
}


int main()
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	return (0);
}

