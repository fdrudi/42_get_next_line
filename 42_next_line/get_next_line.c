/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:14:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/01/22 15:09:18 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <stddef.h>


size_t	ft_strlen(const char *s)
{
	size_t	i;
	
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*united;
	int		i;
	int		j;

	i = 0;
	j = 0;

	if (s2 == NULL)
		return (NULL);

	united = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (united == NULL)
		return (NULL);
	while (s1[j] != '\0')
		united[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		united[i++] = s2[j++];
	united[i] = '\0';
	printf("%s\n", united);
	return (united);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) + 1;
	while (i--)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	return (0);
}

char	*read_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	size_t	file_len;
	char	*tmp;

	file_len = 1;
	tmp = malloc (1);
	tmp[0] = '\0';
	while (file_len != 0 && ft_strchr(buf, '\n') == 0)
	{
		file_len = read(fd, buf, BUFFER_SIZE);
		buf[file_len] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	printf("%s\n", tmp);
	return (tmp);
}

char	*define_line(char *dst)
{
	int		i;
	int		x;
	char	*new;

	i = 0;
	while (dst[i - 1] != '\n' && dst[i] != '\0')
		i++;
	new = (char *) malloc (i + 1);
	if (!new)
	return (NULL);
	x = 0;
	while (i--)
	{
		new[x] = dst[x];
		x++;
	}
	new[x] = '\0';
	printf("%s\n", new);
	return (new);

}

char	*get_next_line(int fd)
{
	char	*dst;
	char	*new;
//	static int	count;

	dst = read_line(fd);
	new = define_line(dst);
	return (new);
}


int main()
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	printf("%d\n", fd);
	get_next_line(fd);
	return (0);
}
