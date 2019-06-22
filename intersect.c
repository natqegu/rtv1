#include "rtv1.h"

int		sphere(t_cam ray, t_object *sphere)
{
	float	a;
	float	b;
	float	c;
	float	di;
	float	t;

    rotation(&sphere->normal, sphere->rotation);
	t_vec oc = substract_vec(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, oc);
	c = dot(oc, oc) - pow(sphere->radius, 2);
	di = pow(b, 2) - 4 * a * c;
	if (di < 0)
		return (0);
	t = (-b - sqrt(di)) / (2 * a);
	if (t > 0)
	{
		t_vec added = add_vec(ray.origin, multiply_vec(ray.direction, t));
		ray.normal = normalize(substract_vec(added, sphere->center));
		return (t);
	}
	return (0);
}

int		cylinder(t_cam ray, t_object *cylinder)
{
    rotation(&cylinder->normal, cylinder->rotation);
	t_vec temp = substract_vec(ray.origin, cylinder->center);
	float a = dot(ray.direction, ray.direction) - pow(dot(ray.direction, cylinder->normal), 2);
	float b = 2 * dot(ray.direction, temp) - dot(ray.direction, cylinder->normal) * dot(temp, cylinder->normal);
	float c = dot(temp, temp) + pow(dot(temp, cylinder->normal), 2) - pow(cylinder->radius, 2);
	float di = pow(b, 2) - 4 * a * c;
	float t = (-b - sqrt(di)) / (2 * a);
	if (t > 0.00001)
	{
		t_vec a = add_vec(ray.origin, multiply_vec(ray.direction, t));
		t_vec a1 = substract_vec(a, cylinder->center);
		t_vec a2 = projection(a1, cylinder->normal);
		ray.normal = normalize(multiply_vec(substract_vec(a1, a2), -1));
		return (t);
	}
	return (0);
}

int		plane(t_cam ray, t_object *plane)
{
	float	t;

    rotation(&plane->normal, plane->rotation);
	float q = dot(ray.direction, plane->normal);
	t = dot(substract_vec(plane->center, ray.origin), plane->normal) / q;
	if (t > 0.00001)
	{
		ray.normal = plane->normal;
		return (t);
	}
	
	return (0);
}

int		cone(t_cam ray, t_object *cone)
{
	t_vec oc = normalize(substract_vec(ray.origin, cone->center));

    rotation(&cone->normal, cone->rotation);
	float a = pow(dot(ray.direction, cone->normal), 2) - pow(cos(cone->angle), 2);
	float b = 2 * (dot(ray.direction, cone->normal) * dot(oc, cone->normal) - dot(ray.direction, oc) * pow(cos(cone->angle), 2));
	float c = pow(dot(cone->normal, oc), 2) - dot(oc, oc) * pow(cos(cone->angle), 2);
	float di = pow(b, 2) - 4 * a * c;
	if (di < 0)
		return (0);
	float t = (-b - sqrt(di)) / (2 * a);
	if (t > 0.00001)
	{
		t_vec a = add_vec(ray.origin, multiply_vec(ray.direction, t));
		t_vec a1 = substract_vec(a, cone->center);
		t_vec a2 = multiply_vec(projection(a1, cone->normal), 1 + pow(cone->angle, 2));
		ray.normal = normalize(multiply_vec(substract_vec(a1, a2), -1));
		return (t);
	}
	return (0);
}

void    intersect(t_rtv *rtv, int i, int j, t_object *node)
{
    while (node)
    {
        if (!ft_strcmp(node->type, "cone"))
            if (cone(rtv->cam, node))
                *(int*)(rtv->mlx.img_string + (i + j * H) * 4) =
                (node->color.red << 16 | node->color.green << 8 | node->color.blue);
        if (!ft_strcmp(node->type, "cylinder"))
            if (cylinder(rtv->cam, node))
                *(int*)(rtv->mlx.img_string + (i + j * H) * 4) =
                (node->color.red << 16 | node->color.green << 8 | node->color.blue);
        if (!ft_strcmp(node->type, "plane"))
            if (plane(rtv->cam, node))
                *(int*)(rtv->mlx.img_string + (i + j * H) * 4) =
                (node->color.red << 16 | node->color.green << 8 | node->color.blue);
        if (!ft_strcmp(node->type, "sphere"))
            if (sphere(rtv->cam, node))
                *(int*)(rtv->mlx.img_string + (i + j * H) * 4) =
                (node->color.red << 16 | node->color.green << 8 | node->color.blue);
        node = node->next;
    }
    
}