/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:32:41 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/29 12:51:24 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (*haystack)
	{
		n = needle;
		if (*haystack == *n)
		{
			h = haystack;
			while (*h == *n)
			{
				h++;
				n++;
				if (*n == '\0')
					return ((char *)haystack);
			}
		}
		haystack++;
	}
	return (NULL);
}
