/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:24:00 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/27 18:48:19 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned long	i;

	i = 0;
	while (i < len)
	{
		if (src[i])
		{
			dst[i] = src[i];
		}
		else
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		i++;
	}
	return (dst);
}
