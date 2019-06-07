/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:10:17 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/25 16:10:19 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	size_t	len;
	char	*result;

	len = ft_strnlen(s1, n);
	if ((result = ft_strnew(len)))
	{
		i = 0;
		while (i < len)
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
