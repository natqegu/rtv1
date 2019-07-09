/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 11:36:48 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 11:41:07 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	mag(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float	clamp(float x, float a, float b)
{
	if (x > b)
		return (b);
	else if (x < a)
		return (a);
	else
		return (x);
}

t_rgb	mult_col(t_rgb c, float scaler)
{
	t_rgb a;

	a.red = c.red * scaler;
	a.green = c.green * scaler;
	a.blue = c.blue * scaler;
	return (a);
}

int		shadow_intersect(t_object *objects, t_vec hit_point,
					t_vec vector_to_light, float max_dist)
{
	float		t;
	t_object	*node;
	t_cam		ray;

	node = objects;
	t = 0;
	ray.origin = hit_point;
	ray.direction = vector_to_light;
	while (node)
	{
		t = choose_object(node, ray);
		if (t >= 0.0001 && t <= max_dist)
			return (1);
		node = node->next;
	}
	return (0);
}
