/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:06:20 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/27 15:58:34 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*src1;
	unsigned char		*dst1;
	size_t				i;
	unsigned char		s;

	src1 = (unsigned char *)src;
	dst1 = (unsigned char *)dst;
	s = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*dst1 = src1[i];
		dst1++;
		if (src1[i] == s)
			return (dst1);
		i++;
	}
	return (NULL);
}
