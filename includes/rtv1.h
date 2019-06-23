#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

# define W 700
# define H 900

# define INFIN 1000
# define EPSILON 0.0001

typedef	struct		s_ray
{	
	t_vec			origin;
	t_vec			direction;
	t_vec			normal;
}					t_ray;

typedef	struct		s_shade
{	
	t_rgb			diffuse;

}					t_shade;

typedef	struct		s_cam
{	
	t_vec			origin;
	t_vec			direction;
	t_vec			rotation;
}					t_cam;

typedef	struct		s_object
{	
	t_vec			center;
	t_vec			origin;
	t_vec			normal;
	t_vec			new_normal;
	t_vec			rotation;
	float			radius;
	float			angle;
	t_rgb			color;
	struct s_object	*next;
	char			*type;
}					t_object;

typedef struct		s_rtv
{	
	struct	
	{	
		void		*init;
		void		*win;
		void		*img;
		char		*img_string;
		int			endian;
		int			line_size;
		int			bpp;
	}				mlx;
	t_cam			cam;
	char			*img;
	char			*name;
	char			**data;
	int				lines;
	t_object		*lights;
	t_object		*objects;
}               	t_rtv;

int					error(int error);
int					parse_manager(t_rtv *rtv);


void				rotate_x(t_vec *v, float ang);
void				rotate_y(t_vec *v, float ang);
void				rotate_z(t_vec *v, float ang);
void				rotation(t_vec *what, t_vec how);

// int		sphere(t_cam ray);
// int		cylinder(t_cam ray);
// int		plane(t_cam ray);
// int		cone(t_cam ray);


t_rgb create_rgb(int r, int g, int b);

t_vec	normalize(t_vec vec);
float	dot(t_vec a, t_vec b);
t_vec	projection(t_vec a, t_vec b);
t_rgb	shade(t_rtv *rtv, t_object *temp_node, t_vec hit_point);
t_rgb   intersect(t_rtv *rtv, t_object **node);
int    	shadow_intersect(t_object *objects, t_vec hit_point, t_vec vector_to_light, float max_dist);
float	choose_object(t_object *node, t_cam ray);
void	print_vec(t_vec a);

#endif