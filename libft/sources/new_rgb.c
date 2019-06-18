/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:49:18 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/15 12:49:21 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rgb	new_rgb(int red, int green, int blue)
{
	t_rgb col;

	col.red = red;
	col.blue = blue;
	col.green = green;
	return (col);
}
