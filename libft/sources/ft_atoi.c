/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 12:59:27 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/29 14:33:37 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_space(char c)
{
	if (c == '\t' || c == '\n' ||
		c == '\r' || c == '\v' ||
		c == ' ' || c == '\f')
		return (0);
	return (1);
}

int		ft_atoi(const char *str)
{
	int					n;
	int					i;
	unsigned long int	result;

	n = 1;
	i = 0;
	result = 0;
	while (!ft_space(str[i]))
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		if (result >= 9223372036854775807 && n == 1)
			return (-1);
		else if (result > 9223372036854775807 && n == -1)
			return (0);
		i++;
	}
	return (result * n);
}
