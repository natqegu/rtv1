/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:56:03 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/28 11:36:07 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	s;
	size_t			i;
	unsigned char	*a;

	s = (unsigned char)c;
	a = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		a[i] = s;
		i++;
	}
	return (a);
}
