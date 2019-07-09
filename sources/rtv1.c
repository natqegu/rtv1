/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 11:04:58 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/23 11:14:44 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rtv1(t_rtv *rtv)
{
	int			i;
	int			j;
	t_object	*node;
	t_rgb		rgb;

	i = 0;
	node = rtv->objects;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			rtv->cam = create_cam(rtv, j, i);
			rgb = intersect(rtv, &node);
			*(int*)(rtv->mlx.img_string + (j + i * W) * 4) =
				(rgb.red << 16 | rgb.green << 8 | rgb.blue);
			j++;
		}
		i++;
	}
}

t_cam	create_cam(t_rtv *rtv, int i, int j)
{
	t_vec	c;
	t_vec	pl;
	t_vec	forw;
	t_vec	up;
	t_vec	right;

	c.x = (2.0f * i) / W - 1;
	c.y = -(2.0f * j) / H + 1;
	pl.x = tan((30.0f * M_PI) / 180.0f);
	pl.y = pl.x * W / H;
	forw = normalize(substract_vec(create_vec(0, 0, 1.0f), rtv->cam.origin));
	right = normalize(cross_vec(forw, create_vec(0, 1.0f, 0)));
	up = cross_vec(right, forw);
	rtv->cam.direction.x = pl.y * c.x * right.x + pl.x * c.y * up.x + forw.x;
	rtv->cam.direction.y = pl.y * c.x * right.y + pl.x * c.y * up.y + forw.y;
	rtv->cam.direction.z = pl.y * c.x * right.z + pl.x * c.y * up.z + forw.z;
	rtv->cam.direction = normalize(rtv->cam.direction);
	rotation(&rtv->cam.direction, rtv->cam.rotation);
	return (rtv->cam);
}

void	del_lst(t_object *obj)
{
	t_object	*fst;
	t_object	*tmp;

	fst = obj;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
}

t_vec	projection(t_vec a, t_vec b)
{
	return (multiply_vec(b, dot(a, b) / dot(b, b)));
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
