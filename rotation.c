#include "rtv1.h"

void	rotate_x(t_vec *v, float ang)
{
	float tmp;

	ang = ang * M_PI / 180.0;
	tmp = v->y;
	v->y = v->y * cos(ang) - v->z * sin(ang);
	v->z = tmp * sin(ang) + v->z * cos(ang);
}

void	rotate_y(t_vec *v, float ang)
{
	float tmp;

	ang = ang * M_PI / 180.0;
	tmp = v->z;
	v->z = v->z * cos(ang) - v->x * sin(ang);
	v->x = tmp * sin(ang) + v->x * cos(ang);
}

void	rotate_z(t_vec *v, float ang)
{
	float tmp;

	ang = ang * M_PI / 180.0;
	tmp = v->x;
	v->x = v->x * cos(ang) - v->y * sin(ang);
	v->y = tmp * sin(ang) + v->y * cos(ang);
}

void    rotation(t_vec *what, t_vec how)
{
    rotate_x(what, how.x);
	rotate_y(what, how.y);
	rotate_z(what, how.z);
}