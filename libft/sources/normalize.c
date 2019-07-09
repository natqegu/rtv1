/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 06:19:55 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 06:20:23 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	normalize(t_vec vec)
{
	t_vec	norm;
	float	divisor;

	divisor = sqrt(dot(vec, vec));
	norm.x = vec.x / divisor;
	norm.y = vec.y / divisor;
	norm.z = vec.z / divisor;
	return (norm);
}
