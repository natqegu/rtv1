#include "rtv1.h"

int    shadow_intersect(t_object *objects, t_vec hit_point, t_vec vector_to_light, float max_dist)
{
	float		t;
    t_object    *node;
    t_cam       ray;
    
    node = objects;
    t = 0;
    ray.origin = hit_point;
    ray.direction = vector_to_light;
    while (node)
    {
		t = choose_object(node, ray);
        if (t > EPSILON && t < max_dist)
		    return (1);
        node = node->next;
    }
    return (0);
}