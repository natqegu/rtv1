/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 11:19:54 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 11:29:27 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	get_specular(t_vec cam_pos, t_vec light_pos,
					t_vec hit, t_object *object)
{
	t_vec	delta;
	t_vec	vector_to_hit;
	t_vec	vector_to_light;

	vector_to_hit = normalize(substract_vec(cam_pos, hit));
	vector_to_light = normalize(substract_vec(light_pos, hit));
	delta = normalize(add_vec(vector_to_hit, vector_to_light));
	return (pow(dot(delta, object->new_normal), object->koef.x));
}

float	get_diffuce(t_rtv *rtv, t_vec light_pos,
				t_vec hit, t_object *object)
{
	t_vec	vector_to_light;
	float	ldist;
	float	cos_teta;
	int		is_shadow;

	vector_to_light = substract_vec(light_pos, hit);
	ldist = mag(vector_to_light);
	vector_to_light = normalize(vector_to_light);
	cos_teta = dot(vector_to_light, multiply_vec(object->new_normal, 1));
	if (cos_teta < 0)
		return (0);
	is_shadow = shadow_intersect(rtv->objects, hit,
									vector_to_light, ldist);
	if (is_shadow)
		return (0);
	return (cos_teta * (object->koef.y / 10.0f));
}

t_rgb	gamma_correction(float fd, float fa, float fs, t_rgb c)
{
	float r;
	float g;
	float b;

	r = (c.red / 255.0f) * (fd + fa + 0.7 * fs);
	g = (c.green / 255.0f) * (fd + fa + 0.7 * fs);
	b = (c.blue / 255.0f) * (fd + fa + 0.7 * fs);
	r = clamp((1.0f - exp(r * -2)), 0.0f, 1.0f);
	g = clamp((1.0f - exp(g * -2)), 0.0f, 1.0f);
	b = clamp((1.0f - exp(b * -2)), 0.0f, 1.0f);
	return (new_rgb((r * 255), (g * 255), (b * 255)));
}

t_rgb	shade(t_rtv *rtv, t_object *temp_node, t_vec hit)
{
	float		final_diffuse;
	float		final_specular;
	float		final_ambient;
	t_object	*lights;

	hit = add_vec(hit, multiply_vec(temp_node->new_normal,
												rtv->little));
	final_diffuse = 0;
	final_specular = 0;
	final_ambient = temp_node->koef.z / 100.0f;
	lights = rtv->lights;
	while (lights)
	{
		final_diffuse += get_diffuce(rtv, lights->origin, hit, temp_node);
		if (!shadow_intersect(rtv->objects, hit, substract_vec(
		lights->origin, hit), mag(substract_vec(lights->origin, hit))))
			final_specular += get_specular(rtv->cam.origin, lights->origin,
														hit, temp_node);
		lights = lights->next;
	}
	return (gamma_correction(final_diffuse, final_specular,
				final_ambient, temp_node->color));
}
