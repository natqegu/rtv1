/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:16:29 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 09:21:12 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (error == 6)
		ft_putendl("Please, choose another x for plane normal(not 0)");
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

int		escape(void)
{
	exit(0);
	return (0);
}

int		esc_key(int keycode)
{
	if (keycode == 53)
		escape();
	return (0);
}

int		main(int argc, char **argv)
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
	rtv1(rtv);
	mlx_hook(rtv->mlx.win, 2, 5, esc_key, &rtv);
	mlx_hook(rtv->mlx.win, 17, 0, escape, &rtv);
	mlx_expose_hook(rtv->mlx.win, esc_key, &rtv);
	mlx_put_image_to_window(rtv->mlx.init, rtv->mlx.win, rtv->mlx.img, 0, 0);
	mlx_loop(rtv->mlx.init);
	free(rtv);
	return (0);
}
