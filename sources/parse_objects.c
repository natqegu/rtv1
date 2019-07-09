/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:54:30 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 10:54:33 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	parse_line(char *str, t_vec vec)
{
	char	**line;
	char	**coord;

	line = ft_strsplit(str, ':');
	coord = ft_strsplit(line[1], ';');
	if (coord && coord[0] && coord[1] && coord[2])
	{
		vec.x = (float)ft_atoi(coord[0]);
		free(coord[0]);
		vec.y = (float)ft_atoi(coord[1]);
		free(coord[1]);
		vec.z = (float)ft_atoi(coord[2]);
		free(line[0]);
		free(coord[2]);
		free(coord);
		free(line[1]);
		free(line);
		return (vec);
	}
	return (create_vec(0, 0, 0));
}

t_rgb	parse_color(char *str, t_rgb rgb)
{
	char	**line;
	char	**coord;

	line = ft_strsplit(str, ':');
	coord = ft_strsplit(line[1], ';');
	if (coord && coord[0] && coord[1] && coord[2])
	{
		rgb.red = ft_atoi(coord[0]);
		free(coord[0]);
		rgb.green = ft_atoi(coord[1]);
		free(coord[1]);
		rgb.blue = ft_atoi(coord[2]);
		free(line[0]);
		free(coord[2]);
		free(coord);
		free(line[1]);
		free(line);
		return (rgb);
	}
	return (new_rgb(0, 0, 0));
}

float	parse_var(char *str, float var)
{
	char	**line;

	line = ft_strsplit(str, ':');
	if (line && line[0] && line[1])
	{
		free(line[0]);
		var = (float)ft_atoi(line[1]);
		free(line[1]);
		free(line);
		return (var);
	}
	return (0.0f);
}

void	parse_lights(t_rtv *rtv, char **lines, int i)
{
	t_object *light;

	light = (t_object *)malloc(sizeof(t_object));
	if (ft_strstr(lines[i + 1], "origin"))
		light->origin = parse_line(lines[i + 1], light->origin);
	light->next = NULL;
	rtv->lights = add_lights_list(rtv, light);
}

void	define_type(int type, t_object *rtv)
{
	if (type == 1)
		rtv->type = "plane";
	if (type == 2)
		rtv->type = "sphere";
	if (type == 3)
		rtv->type = "cone";
	if (type == 4)
		rtv->type = "cylinder";
}
