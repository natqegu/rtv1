#include "rtv1.h"

# define EXP 2
# define CLAMP(x, a, b) (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))
# define BLIK 300


// VECTOR 0 ON PLANE !!!!

float	mag(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

void	print_vec(t_vec a)
{
	printf("x: %f, y: %f, z: %f \n", a.x, a.y, a.z);
}
void	print_col(t_rgb a)
{
	printf("x: %d, y: %d, z: %d \n", a.red, a.green, a.blue);
}

static	float		get_specular(t_vec cam_pos, t_vec light_pos, t_vec hit_point, t_vec normal)
{
	t_vec			delta;
	t_vec			vector_to_hit;
	t_vec			vector_to_light;
	float			cos_teta;

	vector_to_hit = normalize(substract_vec(cam_pos, hit_point));
	vector_to_light = normalize(substract_vec(light_pos, hit_point));
	delta = normalize(add_vec(vector_to_hit, vector_to_light));
	cos_teta = pow(dot(delta, normal), BLIK); /* SIZE OF BLEAK */
	return (cos_teta * 1); // todo: add k
}


static float		get_diffuce(t_rtv *rtv, t_vec light_pos, t_vec hit_point, t_vec normal)
{
	t_vec			vector_to_light;
	float			ldist;
    // float           max_dist;
	float			cos_teta;
	int			    isShadow;

	vector_to_light = substract_vec(light_pos, hit_point);
	ldist = mag(vector_to_light);
	vector_to_light = normalize(vector_to_light);
	cos_teta = dot(vector_to_light, multiply_vec(normal, 1));
	if (cos_teta < 0)
		return (0);
    // max_dist = ldist;
	isShadow = shadow_intersect(rtv->objects, hit_point, vector_to_light, ldist);
    if (isShadow) {
        return (0);
    }
	return (cos_teta * 0.3); // add k
}

static t_rgb		gamma_correction(float fd, float fa, float fs, t_rgb c)
{
    float r;
    float g;
    float b;

	r = (c.red / 255.0f) * (fd + fa + 0.7 * fs);
	g = (c.green / 255.0f) * (fd + fa + 0.7 * fs);
	b = (c.blue / 255.0f) * (fd + fa + 0.7 * fs);
	r = CLAMP((1.0f - exp(r * -(EXP))), 0.0f, 1.0f);
	g = CLAMP((1.0f - exp(g * -(EXP))), 0.0f, 1.0f);
	b = CLAMP((1.0f - exp(b * -(EXP))), 0.0f, 1.0f);
	return (create_rgb((r * 255), (g * 255), (b * 255)));
}

t_rgb   mult_col(t_rgb c, float scaler)
{
    t_rgb a;

    a.red = c.red * scaler;
    a.green = c.green * scaler;
    a.blue = c.blue * scaler;

    return (a);
}


t_rgb	shade(t_rtv *rtv, t_object *temp_node, t_vec hit_point)
{
	float	final_diffuse;
	float	final_specular;
	float	final_ambient;
	t_object *lights;
    t_rgb     color;

    hit_point = add_vec(hit_point, multiply_vec(temp_node->new_normal, EPSILON));  
	final_diffuse = 0;
	final_specular = 0;
	final_ambient = 0.18;
	lights = rtv->lights;


	while (lights)
	{
		final_diffuse += get_diffuce(rtv, lights->origin, hit_point, temp_node->new_normal);
		// todo:: no specular if shadow !!!!!
       // if (!!!shadow )
       if (!shadow_intersect(rtv->objects, hit_point, substract_vec(lights->origin, hit_point), mag(substract_vec(lights->origin, hit_point))))
		    final_specular += get_specular(rtv->cam.origin, lights->origin, hit_point, temp_node->new_normal);
		lights = lights->next;
	}

    color = gamma_correction(final_diffuse, final_specular, final_ambient, temp_node->color);
    return (color);
}