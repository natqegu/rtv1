/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:23:05 by nnovikov          #+#    #+#             */
/*   Updated: 2018/11/04 16:50:19 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(s);
	if (s[i] == '-')
		i++;
	while (i < len)
	{
		tmp = s[i];
		s[i] = s[len - 1];
		s[len - 1] = tmp;
		len--;
		i++;
	}
	return (s);
}
