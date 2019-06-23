#include "rtv1.h"

static void	ft_strjoin_free(char *s1, char *s2, int type)
{
	if (type == 'l')
		free(s1);
	else if (type == 'r')
		free(s2);
	else if (type == 'b')
	{
		free(s1);
		free(s2);
	}
}

char		*ft_strjoin_fake(char *s1, char *s2, char type)
{
	char	*n;
	int		i[2];

	i[0] = 0;
	while (s1[i[0]])
		i[0]++;
	i[1] = 0;
	while (s2[i[1]])
		i[1]++;
	n = (char *)malloc(sizeof(char) * (i[0] + i[1] + 1));
	i[0] = 0;
	while (s1[i[0]])
	{
		n[i[0]] = s1[i[0]];
		i[0]++;
	}
	i[1] = 0;
	while (s2[i[1]])
	{
		n[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	ft_strjoin_free(s1, s2, type);
	n[i[0] + i[1]] = '\0';
	return (n);
}

int		ft_linelen(char *buf, int k)
{
	int	len;

	len = 0;
	while (buf[k] != '\n' && buf[k] != '\0')
	{
		k++;
		len++;
	}
	return (++len);
}

char	**get_scene(char *buf, int lines)
{
	int		i;
	int		k;
	int		j;
	char	**data;

	k = 0;
	j = 0;
	if (!buf)
		return (0);
	if (!(data = (char **)malloc(sizeof(char *) * (lines + 1))))
		return (0);
	while (buf[k] != '\0' && j < lines)
	{
		i = 0;
		if (!(data[j] = ft_strnew(ft_linelen(buf, k))))
			return (0);
		while (buf[k] != '\n' && buf[k] != '\0')
			data[j][i++] = buf[k++];
		data[j][i] = '\0';
		k++;
		j++;
	}
	ft_strdel(&buf);
	return (data);
}

t_vec	parse_line(char *str, t_vec vec)
{
	char	**line;
	char	**coord;

	line = ft_strsplit(str, ':');
	free(line[0]);
	coord = ft_strsplit(line[1], ';');
	vec.x = (float)ft_atoi(coord[0]);
	free(coord[0]);
	vec.y = (float)ft_atoi(coord[1]);
	free(coord[1]);
	vec.z = (float)ft_atoi(coord[2]);
	free(coord[2]);
	free(coord);
	free(line[1]);
	free(line);
	return (vec);
}

t_rgb	parse_color(char *str, t_rgb rgb)
{
	char	**line;
	char	**coord;

	line = ft_strsplit(str, ':');
	free(line[0]);
	coord = ft_strsplit(line[1], ';');
	rgb.red = ft_atoi(coord[0]);
	free(coord[0]);
	rgb.green = ft_atoi(coord[1]);
	free(coord[1]);
	rgb.blue = ft_atoi(coord[2]);
	free(coord[2]);
	free(coord);
	free(line[1]);
	free(line);
	return (rgb);
}

float	parse_var(char *str, float var)
{
	char	**line;

	line = ft_strsplit(str, ':');
	free(line[0]);
	var = (float)ft_atoi(line[1]);
	free(line[1]);
	free(line);
	return (var);
}

t_object	*add_objects_list(t_rtv *rtv, t_object *link)
{
	t_object	*head;

	head = rtv->objects;
	if (rtv->objects == NULL)
		return (link);
	while (rtv->objects->next != NULL)
		rtv->objects = rtv->objects->next;
	rtv->objects->next = link;
	return (head);
}

t_object	*add_lights_list(t_rtv *rtv, t_object *link)
{
	t_object	*head;

	head = rtv->lights;
	if (rtv->lights == NULL)
		return (link);
	while (rtv->lights->next != NULL)
		rtv->lights = rtv->lights->next;
	rtv->lights->next = link;
	return (head);
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

void	parse_obj(t_rtv *rtv, char **lines, int i, int type)
{
	t_object	*object;
	int	k;

	k = i + 6;
	object = (t_object *)malloc(sizeof(t_object));
	while (i < k)
	{
		if (ft_strstr(lines[i], "center"))
			object->center = parse_line(lines[i], object->center);
		if (ft_strstr(lines[i], "normal"))
			object->normal = parse_line(lines[i], object->normal);
		if (ft_strstr(lines[i], "color"))
			object->color = parse_color(lines[i], object->color);
		if (ft_strstr(lines[i], "rotation"))
			object->rotation = parse_line(lines[i], object->rotation);
		if (ft_strstr(lines[i], "angle"))
			object->angle = parse_var(lines[i], object->angle);
		if (ft_strstr(lines[i], "radius"))
			object->radius = parse_var(lines[i], object->radius);
		i++;
	}
	rotation(&object->normal, object->rotation);
	define_type(type, object);
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
		if (ft_strstr(rtv->data[i], "plane {") && !ft_strcmp("}", rtv->data[i + 5]))
			parse_obj(rtv, rtv->data, i, 1);
		if (ft_strstr(rtv->data[i], "sphere {") && !ft_strcmp("}", rtv->data[i + 6]))
			parse_obj(rtv, rtv->data, i, 2);
		if (ft_strstr(rtv->data[i], "cone {") && !ft_strcmp("}", rtv->data[i + 6]))
			parse_obj(rtv, rtv->data, i, 3);
		if (ft_strstr(rtv->data[i], "cylinder {") && !ft_strcmp("}", rtv->data[i + 6]))
			parse_obj(rtv, rtv->data, i, 4);
		i++;
	}
}

int	parse(t_rtv *rtv)
{
	if (ft_strcmp("scene {", rtv->data[0]) && ft_strcmp("}", rtv->data[rtv->lines - 1]))
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
	if (!ft_strcmp("objects {", rtv->data[5]) && !ft_strcmp("}", rtv->data[rtv->lines - 2]))
		parse_objects(rtv);
	return (0);
}

int		parse_manager(t_rtv *rtv)
{
	int		fd;
	char	*buf;
	char	*line;

	buf = ft_strnew(1);
	rtv->objects = NULL;
	rtv->lights = NULL;
	if (!(fd = open(rtv->name, O_RDONLY)))
		return (0);
	while (get_next_line(fd, &line))
	{
		char *trim;
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
	if (!parse(rtv))
		return (0);
	close(fd);
	return (1);
}