/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:53:18 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/31 12:19:09 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	int				l;

	l = (int)len;
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (dst1 <= src1)
		ft_memcpy(dst1, src1, len);
	else
	{
		l--;
		while (l >= 0)
		{
			dst1[l] = src1[l];
			l--;
		}
	}
	return (dst);
}
