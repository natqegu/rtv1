/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:54:54 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 11:02:42 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		**get_scene(char *buf, int lines)
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
