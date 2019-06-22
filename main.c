#include "rtv1.h"

int		error(int error)
{
    if (error == 1)
        ft_putendl("USAGE: ./RTv1 [source map]");
    if (error == 2)
        ft_putendl("File is not valid");
	if (error == 3)
        ft_putendl("Parsing failed");
	if (error == 4)
        ft_putendl("There is no scene");
	if (error == 5)
		ft_putendl("There is no camera after scene");
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

t_cam    create_cam(t_rtv *rtv, int i, int j)
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
	forward = normalize(substract_vec(create_vec(0, 0, 1.0), rtv->cam.origin));
	right = normalize(cross_vec(forward, create_vec(0, 1.0, 0)));
	up = cross_vec(right, forward);
	rtv->cam.direction.x = w_plane * x_cam_space * right.x + h_plane * y_cam_space * up.x + forward.x;
	rtv->cam.direction.y = w_plane * x_cam_space * right.y + h_plane * y_cam_space * up.y + forward.y;
	rtv->cam.direction.z = w_plane * x_cam_space * right.z + h_plane * y_cam_space * up.z + forward.z;
	rtv->cam.direction = normalize(rtv->cam.direction);
	rotation(&rtv->cam.direction, rtv->cam.rotation);
	return (rtv->cam);
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

void	del_lst(t_object *obj)
{
	t_object	*fst;
	t_object	*tmp;

	fst = obj;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
}

void	rtv1(t_rtv *rtv)
{
	int i;
	int j;
	t_object	*node;

	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			node = rtv->objects;
			rtv->cam = create_cam(rtv, i, j);
			intersect(rtv, i, j, node);
			// del_lst(node);
			j++;
		}
		i++;
	}
}

int		escape(void)
{
	system("leaks -q RTv1");
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
	rtv->lines = 0;
	parse_manager(rtv);
	// printf("plane%f\n", rtv->objects->radius);
	rtv1(rtv);
	mlx_hook(rtv->mlx.win, 2, 5, esc_key, &rtv);
	mlx_hook(rtv->mlx.win, 17, 0, escape, &rtv);
	mlx_put_image_to_window(rtv->mlx.init, rtv->mlx.win, rtv->mlx.img, 0, 0);
	mlx_loop(rtv->mlx.init);
	free(rtv);
    return (0);
}