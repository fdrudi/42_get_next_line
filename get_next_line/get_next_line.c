/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:14:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/01/24 13:09:56 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *dst)
{
	int		file_len;
	char	*buf;

	buf = (char *) malloc ((sizeof(char) * BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	file_len = 1;
	while (file_len != 0 && ft_strchr(dst, '\n') == 0)
	{
		file_len = read(fd, buf, BUFFER_SIZE);
		if (file_len == -1)
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

char	*ft_define_line(char *dst)
{
	char	*new;
	int		i;

	i = 0;
	if (!dst[i])
		return (NULL);
	while (dst[i] != '\n' && dst[i] != '\0')
		i++;
	new = (char *) malloc (sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (dst[i] && dst[i] != '\n')
	{
		new[i] = dst[i];
		i++;
	}
	if (dst[i] == '\n')
	{
		new[i] = dst[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char		*new;
	static char	*dst;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	dst = ft_read_line(fd, dst);
	if (!dst)
		return (NULL);
	new = ft_define_line(dst);
	dst = ft_new_dst(dst);
	return (new);
}
