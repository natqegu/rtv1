/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:18:31 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 10:21:07 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	normalno_zh_cone(t_object *cone, t_cam ray, float t)
{
	t_vec vec;

	vec = normalize(multiply_vec(substract_vec(substract_vec(add_vec(
		ray.origin, multiply_vec(ray.direction, t)), cone->center),
			multiply_vec(projection(substract_vec(add_vec(ray.origin,
			multiply_vec(ray.direction, t)), cone->center), cone->normal),
			1 + pow(tan(cone->angle), 2.0f))), 1));
	return (vec);
}

t_vec	normalno_zh_cylinder(t_object *cyl, t_cam ray, float t)
{
	t_vec vec;

	vec = normalize(multiply_vec(substract_vec(substract_vec(add_vec(ray.origin,
								multiply_vec(ray.direction, t)), cyl->center),
								projection(substract_vec(add_vec(ray.origin,
								multiply_vec(ray.direction, t)), cyl->center),
								cyl->normal)), -1));
	return (vec);
}

float	choose_object(t_object *node, t_cam ray)
{
	float t;

	if (!ft_strcmp(node->type, "cone"))
		t = cone(ray, node);
	if (!ft_strcmp(node->type, "cylinder"))
		t = cylinder(ray, node);
	if (!ft_strcmp(node->type, "plane"))
		t = plane(ray, node);
	if (!ft_strcmp(node->type, "sphere"))
		t = sphere(ray, node);
	return (t);
}

t_rgb	intersect(t_rtv *rtv, t_object **node)
{
	float		t;
	float		t_min;
	t_object	*temp_node;
	t_object	*i;

	i = *node;
	t_min = rtv->big;
	while (i)
	{
		t = choose_object(i, rtv->cam);
		if (t >= rtv->little && t <= rtv->big)
			if (t_min >= t)
			{
				t_min = t;
				temp_node = i;
			}
		i = i->next;
	}
	if (t_min < rtv->little || t_min >= rtv->big || temp_node == NULL)
		return (new_rgb(0, 0, 0));
	if (dot(rtv->cam.direction, temp_node->normal) > 0)
		temp_node->normal = multiply_vec(temp_node->normal, -1);
	return (shade(rtv, temp_node, add_vec(rtv->cam.origin,
					multiply_vec(rtv->cam.direction, t_min))));
}
