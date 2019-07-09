/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:25:45 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 10:00:39 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	sphere(t_cam ray, t_object *sphere)
{
	float a;
	float b;
	float di;
	float t;
	t_vec oc;

	oc = substract_vec(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2.0f * dot(ray.direction, oc);
	di = discriminant(a, b, dot(oc, oc) - pow(sphere->radius, 2.0f));
	if (di < 0)
		return (10000);
	t = (-b - sqrt(di)) / (2.0f * a);
	if (t > 0.0001 && t < 10000)
	{
		sphere->new_normal = normalize(substract_vec(add_vec(ray.origin,
						multiply_vec(ray.direction, t)), sphere->center));
		return (t);
	}
	return (10000);
}

float	cylinder(t_cam ray, t_object *cylinder)
{
	float a;
	float b;
	float di;
	float t;
	t_vec temp;

	temp = substract_vec(ray.origin, cylinder->center);
	a = dot(ray.direction, ray.direction) -
		pow(dot(ray.direction, cylinder->normal), 2.0f);
	b = 2.0f * dot(ray.direction, temp) -
		dot(ray.direction, cylinder->normal) * dot(temp, cylinder->normal);
	di = discriminant(a, b, dot(temp, temp) + pow(dot(temp,
					cylinder->normal), 2.0f) - pow(cylinder->radius, 2.0f));
	if (di <= 0.0f)
		return (10000);
	t = (-b - sqrt(di)) / (2.0f * a);
	if (t > 0.0001 && t < 10000)
	{
		cylinder->new_normal = normalno_zh_cylinder(cylinder, ray, t);
		return (t);
	}
	return (10000);
}

float	plane(t_cam ray, t_object *plane)
{
	float	t;

	t = dot(substract_vec(plane->center, ray.origin), plane->normal) /
							dot(ray.direction, plane->normal);
	if (t > 0.0001 && t < 10000)
	{
		plane->new_normal = plane->normal;
		return (t);
	}
	return (10000);
}

float	cone(t_cam ray, t_object *cone)
{
	float a;
	float b;
	float di;
	float t;
	t_vec temp;

	temp = substract_vec(ray.origin, cone->center);
	a = dot(ray.direction, ray.direction) - (pow(tan(cone->angle), 2.0f)
					+ 1) * pow(dot(ray.direction, cone->normal), 2.0f);
	b = 2.0f * (dot(ray.direction, temp) - (pow(tan(cone->angle), 2.0f)
		+ 1) * dot(ray.direction, cone->normal) * dot(temp, cone->normal));
	di = discriminant(a, b, dot(temp, temp) - (pow(tan(cone->angle),
			2.0f) + 1) * pow(dot(temp, cone->normal), 2.0f));
	if (di <= 0.0f)
		return (10000);
	t = (-b - sqrt(di)) / (2.0f * a);
	if (t > 0.0001 && t < 10000)
	{
		cone->new_normal = normalno_zh_cone(cone, ray, t);
		return (t);
	}
	return (10000);
}
