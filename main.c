#include "rtv1.h"

int		error(int error)
{
    if (error == 1)
        ft_putendl("USAGE: ./RTv1 [source map]");
    if (error == 2)
        ft_putendl("File is not valid");
	return (0);
}

float	dot(t_vec a, t_vec b)
{
	float dot;

	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return (dot);
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

t_ray    create_cam(t_rtv *rtv, int i, int j)
{
	float	x_cam_space;
	float	y_cam_space;
	float	h_plane;
	float	w_plane;
	t_vec	forward;
	t_vec	up;
	t_vec	right;

	x_cam_space = (2 * i) / W - 1;
	y_cam_space = (2 * j) / H - 1;
	h_plane = tan((22.5 * M_PI) / 180);
	w_plane = h_plane * W / H;
	rtv->cam.ray.origin = create_vec(0, 0, 0);
	forward = normalize(substract_vec(create_vec(0, 0, 1), rtv->cam.ray.origin));
	right = normalize(multi_sub_vec(forward, create_vec(0, 1, 0)));
	up = multi_sub_vec(right, forward);
	rtv->cam.ray.direction.x = w_plane * x_cam_space * right.x + h_plane * y_cam_space * up.x + forward.x;
	rtv->cam.ray.direction.y = w_plane * x_cam_space * right.y + h_plane * y_cam_space * up.y + forward.y;
	rtv->cam.ray.direction.z = w_plane * x_cam_space * right.z + h_plane * y_cam_space * up.z + forward.z;
	rtv->cam.ray.direction = normalize(rtv->cam.ray.direction);
	
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
	sphere.radius = 0.2;
	t_vec	oc;

	sphere.center = create_vec(0, 0, 10);
	oc = substract_vec(ray.origin, sphere.center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, oc);
	c = dot(oc, oc) - pow(sphere.radius, 2);
	di = pow(b, 2) - 4 * a * c;
	if (di < 0)
		return (0);
	t = (-b - sqrt(di)) / (2 * a);
	// printf("%f\n", t);
	if (t > 0)
	{
		// t_vec mult = multiply_vec(ray.direction, t);
		// t_vec added = add_vec(ray.origin, mult);
		// ray.normal = normalize(substract_vec(added, sphere.center));
		return (t);
	}
	return (0);
}

int		cylinder(t_ray ray)
{
	// t_vec center = create_vec(0, 0, 10);
	// t_vec oc = substract_vec(ray.origin, center);
	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.direction, ray.origin);
	float c = dot(ray.origin, ray.origin) - 1;
	float di = pow(b, 2) - 4 * a * c;
	float t = (-b - sqrt(di)) / (2 * a);
	// printf("%f\n", t);
	if (t > 1)
		return (0);
	if (t < 1 && t > 0)
		return (1);
	return (0);
}

int		plane(t_ray ray)
{
	t_vec	p;
	float	q = 0;
	float	t;
	t_plane	plane;

	plane.normal = normalize(create_vec(0, 5, 0));
	plane.center = normalize(create_vec(5, 0, 5));
	q = p.x * -plane.normal.x + p.y * -plane.normal.y + p.z * -plane.normal.z;
	t = -(q + p.z * ray.origin.z + p.y * ray.origin.y + p.z * ray.origin.z) /
	(plane.normal.z * ray.direction.z + plane.normal.y * ray.direction.y + plane.normal.z * ray.direction.z);
	if (t < 0)
		return (0);
	if (t > 0)
	{

		return (t);
	}
	
	return (0);
}

int		cone(t_ray ray)
{
	t_cone	cone;
	cone.angle = 45;
	cone.center = normalize(create_vec(0, 10, 0));
	t_vec oc = normalize(substract_vec(ray.origin, cone.center));

	float a = pow(dot(ray.direction, cone.center), 2) - pow(cos(cone.angle), 2);
	float b = 2 * (dot(ray.direction, cone.center) * dot(oc, cone.center) - dot(ray.direction, oc) * pow(cos(cone.angle), 2));
	float c = pow(dot(cone.center, oc), 2) - dot(oc, oc) * pow(cos(cone.angle), 2);
	float di = pow(b, 2) - 4 * a * c;
	if (di < 0)
		return (0);
	float t = (-b - sqrt(di)) / (2 * a);
	// printf("%f\n", t);
	if (t > 0 && t < 10000)
		return (1);
	return (0);
}

void	rtv1(t_rtv *rtv)
{
	int i;
	int j;
	t_ray	ray;
	// t_rgb	rgb = new_rgb(0, 100, 0);
	t_rgb	rgb1 = new_rgb(110, 100, 100);

	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			ray = create_cam(rtv, i, j);
			// if (plane(ray))
			// 	*(int*)(rtv->mlx.img_string + (i + j * H) * 4) = (rgb.red << 16 | rgb.green << 8 | rgb.blue);
			if (sphere(ray))
				*(int*)(rtv->mlx.img_string + (i + j * H) * 4) = (rgb1.red << 16 | rgb1.green << 8 | rgb1.blue);
			j++;
		}
		i++;
	}
}

void	parse()
{
	
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
    rtv->mlx.init = mlx_init();
	rtv->mlx.win = mlx_new_window(rtv->mlx.init, W, H, "RTv1");
	rtv->mlx.img = mlx_new_image(rtv->mlx.init, W, H);
	rtv->mlx.img_string = mlx_get_data_addr(rtv->mlx.img, &rtv->mlx.bpp,
									&rtv->mlx.line_size, &rtv->mlx.endian);
	parse();
	rtv1(rtv);
	mlx_hook(rtv->mlx.win, 2, 5, esc_key, &rtv);
	mlx_hook(rtv->mlx.win, 17, 0, escape, &rtv);
	mlx_put_image_to_window(rtv->mlx.init, rtv->mlx.win, rtv->mlx.img, 0, 0);
	mlx_loop(rtv->mlx.init);
    return (0);
}