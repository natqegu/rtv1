/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:08:20 by nnovikov          #+#    #+#             */
/*   Updated: 2018/11/04 15:56:16 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		total;
	size_t		i;
	size_t		dlen;
	size_t		slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	i = 0;
	total = dlen + slen;
	if (dstsize <= dlen)
		return (slen + dstsize);
	while (dlen < dstsize - 1)
	{
		dst[dlen] = src[i];
		dlen++;
		i++;
	}
	dst[dlen] = '\0';
	return (total);
}
