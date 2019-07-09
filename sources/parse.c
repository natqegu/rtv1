/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:46:45 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 10:51:21 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	define_object(t_object *object, char *line)
{
	if (ft_strstr(line, "center"))
		object->center = parse_line(line, object->center);
	if (ft_strstr(line, "normal"))
		object->normal = parse_line(line, object->normal);
	if (ft_strstr(line, "color"))
		object->color = parse_color(line, object->color);
	if (ft_strstr(line, "rotation"))
		object->rotation = parse_line(line, object->rotation);
	if (ft_strstr(line, "angle"))
		object->angle = parse_var(line, object->angle);
	if (ft_strstr(line, "radius"))
		object->radius = parse_var(line, object->radius);
	if (ft_strstr(line, "koef"))
		object->koef = parse_line(line, object->koef);
}

void	parse_obj(t_rtv *rtv, char **lines, int i, int type)
{
	t_object	*object;
	int			k;

	k = i + 7;
	object = (t_object *)malloc(sizeof(t_object));
	while (i < k)
	{
		define_object(object, lines[i]);
		i++;
	}
	rotation(&object->normal, object->rotation);
	define_type(type, object);
	rtv->big = 10000;
	rtv->little = 0.0001;
	object->next = NULL;
	rtv->objects = add_objects_list(rtv, object);
}

void	parse_objects(t_rtv *rtv)
{
	int i;

	i = 6;
	while (*rtv->data && i < rtv->lines)
	{
		if (ft_strstr(rtv->data[i], "light {"))
			parse_lights(rtv, rtv->data, i);
		if (ft_strstr(rtv->data[i], "plane {") && !ft_strcmp("}",
												rtv->data[i + 6]))
			parse_obj(rtv, rtv->data, i, 1);
		if (ft_strstr(rtv->data[i], "sphere {") && !ft_strcmp("}",
												rtv->data[i + 7]))
			parse_obj(rtv, rtv->data, i, 2);
		if (ft_strstr(rtv->data[i], "cone {") && !ft_strcmp("}",
												rtv->data[i + 7]))
			parse_obj(rtv, rtv->data, i, 3);
		if (ft_strstr(rtv->data[i], "cylinder {") && !ft_strcmp("}",
												rtv->data[i + 7]))
			parse_obj(rtv, rtv->data, i, 4);
		i++;
	}
}

int		parse(t_rtv *rtv)
{
	if (ft_strcmp("scene {", rtv->data[0]) && ft_strcmp("}",
									rtv->data[rtv->lines - 1]))
		return (error(4));
	if (ft_strcmp("camera {", rtv->data[1]) && ft_strcmp("}", rtv->data[4]))
		return (error(5));
	else
	{
		if (ft_strstr(rtv->data[2], "origin"))
			rtv->cam.origin = parse_line(rtv->data[2], rtv->cam.origin);
		if (ft_strstr(rtv->data[3], "rotation"))
			rtv->cam.rotation = parse_line(rtv->data[3], rtv->cam.rotation);
	}
	if (!ft_strcmp("objects {", rtv->data[5]) && !ft_strcmp("}",
											rtv->data[rtv->lines - 2]))
		parse_objects(rtv);
	return (0);
}

int		parse_manager(t_rtv *rtv)
{
	int		fd;
	char	*buf;
	char	*line;
	char	*trim;

	buf = ft_strnew(1);
	rtv->objects = NULL;
	rtv->lights = NULL;
	if (!(fd = open(rtv->name, O_RDONLY)))
		return (0);
	while (get_next_line(fd, &line))
	{
		trim = ft_strtrim(line);
		buf = ft_strjoin_fake(buf, ft_strjoin_fake(trim, "\n", 'l'), 'b');
		free(line);
		rtv->lines++;
	}
	if (!(rtv->data = get_scene(buf, rtv->lines)))
	{
		free(rtv->data);
		return (0);
	}
	parse(rtv);
	close(fd);
	return (1);
}
