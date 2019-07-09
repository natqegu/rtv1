/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 11:25:24 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/15 11:25:27 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	multiply_vec(t_vec a, float mult)
{
	t_vec	res;

	res.x = a.x * mult;
	res.y = a.y * mult;
	res.z = a.z * mult;
	return (res);
}
