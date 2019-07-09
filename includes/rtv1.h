/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:45:20 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 13:51:23 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define W 1200
# define H 900

typedef	struct		s_ray
{
	t_vec			origin;
	t_vec			direction;
	t_vec			normal;
}					t_ray;

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
	t_vec			koef;
	float			radius;
	float			angle;
	t_rgb			color;
	struct s_object	*next;
	char			*type;
}					t_object;

typedef	struct		s_mlx
{
	void			*init;
	void			*win;
	void			*img;
	char			*img_string;
	int				endian;
	int				line_size;
	int				bpp;
}					t_mlx;

typedef struct		s_rtv
{
	t_mlx			mlx;
	t_cam			cam;
	char			*img;
	char			*name;
	char			**data;
	int				lines;
	t_object		*lights;
	t_object		*objects;
	float			big;
	float			little;
}					t_rtv;

int					error(int error);
int					parse_manager(t_rtv *rtv);
int					check_map_name(char *arg);
void				rtv1(t_rtv *rtv);
t_cam				create_cam(t_rtv *rtv, int i, int j);
void				del_lst(t_object *obj);
t_vec				projection(t_vec a, t_vec b);
int					ft_linelen(char *buf, int k);
t_vec				parse_line(char *str, t_vec vec);
t_rgb				parse_color(char *str, t_rgb rgb);
float				parse_var(char *str, float var);
void				parse_lights(t_rtv *rtv, char **lines, int i);
t_object			*add_lights_list(t_rtv *rtv, t_object *link);
t_object			*add_objects_list(t_rtv *rtv, t_object *link);
char				**get_scene(char *buf, int lines);
char				*ft_strjoin_fake(char *s1, char *s2, char type);
void				rotate_x(t_vec *v, float ang);
void				rotate_y(t_vec *v, float ang);
void				rotate_z(t_vec *v, float ang);
void				rotation(t_vec *what, t_vec how);
float				clamp(float x, float a, float b);
t_vec				normalize(t_vec vec);
float				dot(t_vec a, t_vec b);
t_vec				projection(t_vec a, t_vec b);
t_rgb				shade(t_rtv *rtv, t_object *temp_node, t_vec hit_point);
t_rgb				intersection(t_rtv *rtv, t_object **node);
int					shadow_intersect(t_object *objects, t_vec hit_point,
					t_vec vector_to_light, float max_dist);
float				choose_object(t_object *node, t_cam ray);
t_rgb				mult_col(t_rgb c, float scaler);
float				mag(t_vec a);
t_rgb				intersect(t_rtv *rtv, t_object **node);
float				choose_object(t_object *node, t_cam ray);
float				sphere(t_cam ray, t_object *sphere);
float				cylinder(t_cam ray, t_object *cylinder);
float				plane(t_cam ray, t_object *plane);
float				cone(t_cam ray, t_object *cone);
t_vec				normalno_zh_cone(t_object *cone, t_cam ray, float t);
t_vec				normalno_zh_cylinder(t_object *cyl, t_cam ray, float t);
void				define_type(int type, t_object *rtv);

#endif
