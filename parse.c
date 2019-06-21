#include "rtv1.h"

// int	parse(t_rtv *rtv, int fd)
// {
	
// 	return (0);
// }

int		parse_manager(t_rtv *rtv)
{
	int		fd;

	if (!(fd = open(rtv->name, O_RDONLY)))
		return (0);
	close(fd);
	if (!(fd = open(rtv->name, O_RDONLY)))
		return (0);
	// if (!parse(rtv, fd))
	// 	return (0);
	close(fd);
	return (1);
}