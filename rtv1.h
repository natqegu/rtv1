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

# define W 700
# define H 700

typedef	struct	s_ray
{
	t_vec		origin;
	t_vec		direction;
	t_vec		normal;
	float		t_max;
}				t_ray;

typedef struct	s_plane
{
	t_vec		center;
	t_vec		normal;
}				t_plane;

typedef	struct	s_sphere
{
	t_vec		center;
	float		radius;
	t_vec		normal;
}				t_sphere;

typedef	struct	s_cone
{
	t_vec		center;
	float		angle;
	t_vec		normal;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec		center;
	t_vec		normal;
	float		radius;
}				t_cylinder;

typedef	struct	s_shade
{
	t_rgb		diffuse;
	
}				t_shade;

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
	struct
	{
		t_ray	ray;
	}			cam;
	char		*img;
	// t_plane		plane;
	// t_cone		cone;
	// t_cylinder	cylinder;
	// t_sphere	sphere;
	char		*name;
}               t_rtv;

int				parse_manager(t_rtv *rtv);
#endif