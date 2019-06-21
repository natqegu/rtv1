#include "rtv1.h"

int		error(int error)
{
    if (error == 1)
        ft_putendl("USAGE: ./RTv1 [source map]");
    if (error == 2)
        ft_putendl("File is not valid");
	return (0);
}

int		check_map_name(char *arg)
{
	int		fd;
	char	buff[8];

	if (!(fd = open(arg, O_RDONLY)))
		return (0);
	if (read(fd, buff, 8) < 8)
		return (0);
	return (1);
}

float	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

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

t_vec	projection(t_vec a, t_vec b)
{
	return (multiply_vec(b, dot(a, b) / dot(b, b)));
}

void	rotate_x(t_vec *v, float ang)
{
	float tmp;

	ang = ang * M_PI / 180.0;
	tmp = v->y;
	v->y = v->y * cos(ang) - v->z * sin(ang);
	v->z = tmp * sin(ang) + v->z * cos(ang);
}

void	rotate_y(t_vec *v, float ang)
{
	float tmp;

	ang = ang * M_PI / 180.0;
	tmp = v->z;
	v->z = v->z * cos(ang) - v->x * sin(ang);
	v->x = tmp * sin(ang) + v->x * cos(ang);
}

void	rotate_z(t_vec *v, float ang)
{
	float tmp;

	ang = ang * M_PI / 180.0;
	tmp = v->x;
	v->x = v->x * cos(ang) - v->y * sin(ang);
	v->y = tmp * sin(ang) + v->y * cos(ang);
}

t_ray    create_cam(t_rtv *rtv, int i, int j)
{
	float	x_cam_space;
	float	y_cam_space;
	float	h_plane;
	float	w_plane;
	t_vec	forward;
	t_vec	up;
	t_vec	right;

	x_cam_space = (2.0 * i) / W - 1.0;
	y_cam_space = - (2.0 * j) / H + 1.0;
	h_plane = tan((30 * M_PI) / 180.0);
	w_plane = h_plane * W / H;
	rtv->cam.ray.origin = create_vec(0, 0, 0);
	forward = normalize(substract_vec(create_vec(0, 0, 1.0), rtv->cam.ray.origin));
	right = normalize(cross_vec(forward, create_vec(0, 1.0, 0)));
	up = cross_vec(right, forward);
	rtv->cam.ray.direction.x = w_plane * x_cam_space * right.x + h_plane * y_cam_space * up.x + forward.x;
	rtv->cam.ray.direction.y = w_plane * x_cam_space * right.y + h_plane * y_cam_space * up.y + forward.y;
	rtv->cam.ray.direction.z = w_plane * x_cam_space * right.z + h_plane * y_cam_space * up.z + forward.z;
	rtv->cam.ray.direction = normalize(rtv->cam.ray.direction);
	rotate_x(&rtv->cam.ray.direction, 0);
	rotate_y(&rtv->cam.ray.direction, 0);
	rotate_z(&rtv->cam.ray.direction, 0);
	return (rtv->cam.ray);
}


int		sphere(t_ray ray)
{
	float	a;
	float	b;
	float	c;
	float	di;
	float	t;
	t_sphere	sphere;
	sphere.radius = 2.0;

	sphere.center = create_vec(1.8, 0.8, 10);
	t_vec oc = substract_vec(ray.origin, sphere.center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, oc);
	c = dot(oc, oc) - pow(sphere.radius, 2);
	di = pow(b, 2) - 4 * a * c;
	if (di < 0)
		return (0);
	t = (-b - sqrt(di)) / (2 * a);
	if (t > 0)
	{
		t_vec added = add_vec(ray.origin, multiply_vec(ray.direction, t));
		ray.normal = normalize(substract_vec(added, sphere.center));
		return (t);
	}
	rotate_x(&ray.direction, 180);
	rotate_y(&ray.direction, 180);
	rotate_z(&ray.direction, 180);
	return (0);
}

int		cylinder(t_ray ray)
{
	t_cylinder	cylinder;

	cylinder.radius = 2;
	cylinder.center = create_vec(0, 0, 15);
	cylinder.normal = normalize(create_vec(0, 1.0, 0));

	t_vec temp = substract_vec(ray.origin, cylinder.center);
	float a = dot(ray.direction, ray.direction) - pow(dot(ray.direction, cylinder.normal), 2);
	float b = 2 * dot(ray.direction, temp) - dot(ray.direction, cylinder.normal) * dot(temp, cylinder.normal);
	float c = dot(temp, temp) + pow(dot(temp, cylinder.normal), 2) - pow(cylinder.radius, 2);
	float di = pow(b, 2) - 4 * a * c;
	float t = (-b - sqrt(di)) / (2 * a);
	if (t > 0.00001)
	{
		t_vec a = add_vec(ray.origin, multiply_vec(ray.direction, t));
		t_vec a1 = substract_vec(a, cylinder.center);
		t_vec a2 = projection(a1, cylinder.normal);
		ray.normal = normalize(multiply_vec(substract_vec(a1, a2), -1));
		return (t);
	}
	rotate_x(&ray.direction, 80);
	rotate_y(&ray.direction, 0);
	rotate_z(&ray.direction, 0);
	return (0);
}

int		plane(t_ray ray)
{
	float	t;
	t_plane	plane;

	plane.normal = normalize(create_vec(0, 1.0, 0));
	plane.center = normalize(create_vec(0, -57, 0));
	float q = dot(ray.direction, plane.normal);
	t = dot(substract_vec(plane.center, ray.origin), plane.normal) / q;
	if (t > 0.00001)
	{
		ray.normal = plane.normal;
		return (t);
	}
	
	return (0);
}

int		cone(t_ray ray)
{
	t_cone	cone;
	cone.angle = 50;
	cone.center = create_vec(0, 0, 2);
	cone.normal = normalize(create_vec(0, 1.0, 0));
	t_vec oc = normalize(substract_vec(ray.origin, cone.center));

	float a = pow(dot(ray.direction, cone.normal), 2) - pow(cos(cone.angle), 2);
	float b = 2 * (dot(ray.direction, cone.normal) * dot(oc, cone.normal) - dot(ray.direction, oc) * pow(cos(cone.angle), 2));
	float c = pow(dot(cone.normal, oc), 2) - dot(oc, oc) * pow(cos(cone.angle), 2);
	float di = pow(b, 2) - 4 * a * c;
	if (di < 0)
		return (0);
	float t = (-b - sqrt(di)) / (2 * a);
	if (t > 0.00001)
	{
		t_vec a = add_vec(ray.origin, multiply_vec(ray.direction, t));
		t_vec a1 = substract_vec(a, cone.center);
		t_vec a2 = multiply_vec(projection(a1, cone.normal), 1 + pow(cone.angle, 2));
		ray.normal = normalize(multiply_vec(substract_vec(a1, a2), -1));
		return (t);
	}
	return (0);
}

// t_rgb	shade_rgb(t_rgb rgb)
// {

// 	return (rgb);
// }

// t_rgb	shade(t_ray ray, float t)
// {
// 	t_rgb rgb = new_rgb(0, 100, 0);
// 	float t_big = 1000000;

// 	t_vec hit_point = add_vec(ray.origin, multiply_vec(ray.direction, t_big));
// 	t_vec light = cross_vec(create_vec(0, 0, -1), ray.origin);

// 	int	index = 0;
// 	float albedo = 0.18;
// 	ray.t_max = t;
// 	if (ray.t_max < t)
// 		ray.t_max == t;
// 	return (shade_rgb(rgb));
// }

void	rtv1(t_rtv *rtv)
{
	int i;
	int j;
	t_ray	ray;
	t_rgb	rgb = new_rgb(0, 100, 0);
	t_rgb	rgb1 = new_rgb(110, 100, 100);

	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			ray = create_cam(rtv, i, j);
			float t = cylinder(ray);
			// t_rgb rgb = shade(ray, t);
			if (t)
				*(int*)(rtv->mlx.img_string + (i + j * H) * 4) = (rgb.red << 16 | rgb.green << 8 | rgb.blue);
			if (sphere(ray))
				*(int*)(rtv->mlx.img_string + (i + j * H) * 4) = (rgb1.red << 16 | rgb1.green << 8 | rgb1.blue);
			j++;
		}
		i++;
	}
}

int		escape(void)
{
	system("leaks RTv1 -q");
	exit(0);
	return (0);
}

int		esc_key(int keycode)
{
	if (keycode == 53)
		escape();
	return (0);
}

int     main(int argc, char **argv)
{
    t_rtv *rtv;

    if (argc != 2)
        return (error(1));
    if (!check_map_name(argv[1]))
        return (error(2));
	rtv = (t_rtv*)malloc(sizeof(t_rtv));
	rtv->name = argv[1];
    rtv->mlx.init = mlx_init();
	rtv->mlx.win = mlx_new_window(rtv->mlx.init, W, H, "RTv1");
	rtv->mlx.img = mlx_new_image(rtv->mlx.init, W, H);
	rtv->mlx.img_string = mlx_get_data_addr(rtv->mlx.img, &rtv->mlx.bpp,
									&rtv->mlx.line_size, &rtv->mlx.endian);
	parse_manager(rtv);
	rtv1(rtv);
	mlx_hook(rtv->mlx.win, 2, 5, esc_key, &rtv);
	mlx_hook(rtv->mlx.win, 17, 0, escape, &rtv);
	mlx_put_image_to_window(rtv->mlx.init, rtv->mlx.win, rtv->mlx.img, 0, 0);
	mlx_loop(rtv->mlx.init);
    return (0);
}