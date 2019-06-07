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
	int		check;
	int		fd;
	char	*buff[16];

	if ((fd = open(arg, O_RDONLY)) < 0)
		return (0);
	if (!(check = read(fd, buff, 16)))
		return (0);
	if (check < 8)
		return (0);
	return (1);
}

void    create_cam()
{

}

int     main(int argc, char **argv)
{
    t_rtv rtv;

    if (argc != 2)
        return (error(1));
    if (!check_map_name(argv[1]))
        return (error(2));
    rtv.mlx.init = mlx_init();
	rtv.mlx.win = mlx_new_window(rtv.mlx.init, W, H, "RTv1");
	rtv.mlx.img = mlx_new_image(rtv.mlx.init, W, H);
	rtv.mlx.img_string = mlx_get_data_addr(rtv.mlx.img, &rtv.mlx.bpp,
									&rtv.mlx.line_size, &rtv.mlx.endian);
    create_cam();
    return (0);
}