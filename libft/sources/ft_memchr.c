/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:03:36 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/27 16:28:24 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			ch;
	const char		*str;
	size_t			i;

	ch = (char)c;
	str = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (*(str) == ch)
			return ((void *)str);
		i++;
		str++;
	}
	return (NULL);
}
