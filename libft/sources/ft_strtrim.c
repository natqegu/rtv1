/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:20:27 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/29 12:35:36 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int i;
	int len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s) - 1;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (ft_strnew(1));
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	return (ft_strsub(s, i, len - i + 1));
}
