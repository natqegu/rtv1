#include "rtv1.h"

float	discriminant(float a, float b, float c)
{
	return (pow(b, 2) - 4.0f * a * c);
}

float		sphere(t_cam ray, t_object *sphere)
{
	float	a;
	float	b;
	float	di;
	float	t;

	t_vec oc = substract_vec(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2.0f * dot(ray.direction, oc);
	di = discriminant(a, b,	dot(oc, oc) - pow(sphere->radius, 2.0f));
	if (di < 0)
		return (INFIN);
	t = (-b - sqrt(di)) / (2.0f * a);
	if (t > EPSILON && t < INFIN)
	{
		t_vec added = add_vec(ray.origin, multiply_vec(ray.direction, t));
		sphere->new_normal = normalize(substract_vec(added, sphere->center));
		return (t);
	}
	return (INFIN);
}

float		cylinder(t_cam ray, t_object *cylinder)
{
	float a;
	float b;
	float di;
	float t;

	t_vec temp = substract_vec(ray.origin, cylinder->center);
	a = dot(ray.direction, ray.direction) - pow(dot(ray.direction, cylinder->normal), 2.0f);
	b = 2.0f * dot(ray.direction, temp) - dot(ray.direction, cylinder->normal) * dot(temp, cylinder->normal);
	di = discriminant(a, b, dot(temp, temp) + pow(dot(temp, cylinder->normal), 2.0f) - pow(cylinder->radius, 2.0f));
	if (di <= 0.0f)
		return (INFIN);
	t = (-b - sqrt(di)) / (2.0f * a);
	if (t > EPSILON && t < INFIN)
	{
		t_vec a = add_vec(ray.origin, multiply_vec(ray.direction, t));
		t_vec a1 = substract_vec(a, cylinder->center);
		t_vec a2 = projection(a1, cylinder->normal);
		cylinder->new_normal = normalize(multiply_vec(substract_vec(a1, a2), -1));
		return (t);
	}
	return (INFIN);
}

float		plane(t_cam ray, t_object *plane)
{
	float	t;

	t = dot(substract_vec(plane->center, ray.origin), plane->normal) / 
							dot(ray.direction, plane->normal);
	if (t > EPSILON && t < INFIN)
	{
		plane->new_normal = plane->normal;
		return (t);
	}
	return (INFIN);
}

float		cone(t_cam ray, t_object *cone)
{
	float a;
	float b;
	float di;
	float t;

	cone->normal = normalize(cone->normal);
	float d = dot(ray.direction, cone->normal);
	t_vec temp = substract_vec(ray.origin, cone->center);
	float k = tan(cone->angle);
	k = k * k + 1;
	a = dot(ray.direction, ray.direction) - k * d * d;
	b = 2.0f * (dot(ray.direction, temp) - k * d * dot(temp, cone->normal));
	di = discriminant(a, b, dot(temp, temp) - k * pow(dot(temp, cone->normal), 2.0f));
	if (di <= 0.0f)
		return (INFIN);
	t = (-b - sqrt(di)) / (2.0f * a);
	if (t > EPSILON && t < INFIN)
	{
		t_vec a = add_vec(ray.origin, multiply_vec(ray.direction, t));
		t_vec a1 = substract_vec(a, cone->center);
		t_vec a2 = multiply_vec(projection(a1, cone->normal), 1 + pow(tan(cone->angle), 2.0f));
		cone->new_normal = normalize(multiply_vec(substract_vec(a1, a2), -1));
		return (t);
	}
	return (INFIN);
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


t_rgb create_rgb(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.red = r;
	rgb.green = g;
	rgb.blue = b;
	
	return (rgb);
}

t_rgb    intersect(t_rtv *rtv, t_object **node)
{

	float		t;
	float		t_min;
	t_vec		hit_point;
	t_object	*temp_node;
	t_object	*i;
	t_rgb		color;
	
	i = *node;
	t_min = INFIN;
    while (i)
    {
		t = choose_object(i, rtv->cam);
		if (t >= EPSILON && t <= INFIN)
		{
			if (t_min >= t)
			{
				t_min = t;
				temp_node = i;
			}			
		}
        i = i->next;
    }
	if (t_min < EPSILON || t_min >= INFIN || temp_node == NULL)
			return (create_rgb(0, 0, 0));
		hit_point = add_vec(rtv->cam.origin, multiply_vec(rtv->cam.direction, t_min));
		if (dot(rtv->cam.direction, temp_node->normal) > 0)
			temp_node->normal = multiply_vec(temp_node->normal, -1);
		color = shade(rtv, temp_node, hit_point);
	return (color);
}