/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:14:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/01/22 18:55:46 by fdrudi           ###   ########.fr       */
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

	if (!s1 || !s2)
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
	free (s1);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		start = ft_strlen(s);
	if (start + len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	i = 0;
	dest = (char *) malloc (sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (len--)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}


char	*new_buf(char *new, char *buf)
{
	int	len;

	len = ft_strlen(buf) - ft_strlen(new);
	buf = ft_substr(buf, ft_strlen(new), len);
	return (buf);
}

char	*read_line(int fd, char  *buf)
{
	size_t	file_len;
	char	*tmp;

	file_len = 1;
	tmp = malloc (1);
	tmp[0] = '\0';
	if (buf)
		tmp = ft_strjoin(tmp, buf);
	while (file_len != 0 && ft_strchr(buf, '\n') == 0)
	{
		file_len = read(fd, buf, BUFFER_SIZE);
		buf[file_len] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	return (tmp);
}

char	*define_line(char *dst)
{
	char	*new;
	int		i;
	int		x;

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
	static char	*buf;

	buf = malloc (BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	dst = read_line(fd, buf);
	new = define_line(dst);
	if (ft_strlen(buf) > ft_strlen(new))
		new_buf(new, buf);
	return (new);
}


int main()
{
	int fd;
	int	i;

	i = 3;
	fd = open("test.txt", O_RDONLY);
	printf("%d\n", fd);
	while (i--)
		get_next_line(fd);
	return (0);
}
