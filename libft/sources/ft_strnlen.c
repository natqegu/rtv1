/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:47:51 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/26 15:47:52 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	char *ptr;

	if ((ptr = ft_memchr(s, '\0', maxlen)))
		return (size_t)(ptr - s);
	return (maxlen);
}
