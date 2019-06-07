#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"

# define W 1000
# define H 700

typedef struct	s_rtv
{
	struct
	{
		void	*init;
		void	*win;
		void	*img;
		char	*img_string;
		int		endian;
		int		line_size;
		int		bpp;
	}			mlx;
}               t_rtv;
#endif