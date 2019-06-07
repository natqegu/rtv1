/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:10:15 by nnovikov          #+#    #+#             */
/*   Updated: 2018/11/29 14:40:09 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"
#include <unistd.h>
#include <stdlib.h>

static char	*new_one(char *src, size_t len)
{
	char *dst;

	if (!src)
	{
		dst = ft_strnew(len);
		return (dst);
	}
	dst = ft_strnew(ft_strlen(src) + len);
	ft_strcpy(dst, src);
	ft_strdel(&src);
	return (dst);
}

static int	the_line(char **line, char *space)
{
	char	*tmp;
	int		len;

	len = ft_strlen(space);
	tmp = ft_strchr(space, '\n');
	if (tmp)
	{
		*line = new_one(*line, tmp - space);
		ft_strncat(*line, space, tmp - space);
		ft_memmove(space, tmp + 1, ft_strlen(tmp));
		MEOW;
	}
	if (len)
	{
		*line = new_one(*line, len);
		ft_strncat(*line, space, len);
		*space = '\0';
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*space[1024];
	int			retu;

	if (fd < 0 || !line || fd > 1024 ||
		(!space[fd] && !(space[fd] = ft_strnew(BUFF_SIZE + 1))) ||
		read(fd, space[fd], 0) < 0)
		return (-1);
	*line = NULL;
	if (the_line(line, space[fd]))
		MEOW;
	while ((retu = read(fd, space[fd], BUFF_SIZE)) > 0)
	{
		space[fd][retu] = '\0';
		if (the_line(line, space[fd]))
			MEOW;
	}
	if (*line)
		MEOW;
	ft_strdel(&space[fd]);
	if (retu < 0)
		return (-1);
	return (0);
}
