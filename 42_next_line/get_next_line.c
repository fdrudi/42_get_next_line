/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:14:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/01/23 16:38:24 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *dst)
{
	size_t	file_len;
	char	*buf;

	buf = (char *) malloc ((sizeof(char) * BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	file_len = 1;
	while (file_len != 0 && ft_strchr(dst, '\n') == 0)
	{
		file_len = read(fd, buf, BUFFER_SIZE);
		if ((int) file_len == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[file_len] = '\0';
		dst = ft_strjoin(dst, buf);
	}
	free (buf);
	return (dst);
}

char	*define_line(char *dst)
{
	char	*new;
	int		i;
	int		x;

	i = 0;
	if (!dst[i])
		return (NULL);
	while (dst[i - 1] != '\n' && dst[i] != '\0')
		i++;
	new = (char *) malloc (sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	x = 0;
	while (i--)
	{
		new[x] = dst[x];
		x++;
	}
	new[x] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char		*new;
	static char	*dst;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	dst = read_line(fd, dst);
	if (!dst)
		return (NULL);
	new = define_line(dst);
	dst = new_dst(dst);
	return (new);
}
