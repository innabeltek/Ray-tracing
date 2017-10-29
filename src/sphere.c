/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/05/18 15:33:34 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_obj			*create_sphere(t_obj *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere_param(sphere);
	obj->id = (void*)(sphere);
	obj->intersection = sphere_intersect;
	return (obj);
}

void			sphere_param(t_sphere *sphere)
{
	sphere->pos.x = 600;
	sphere->pos.y = 300;
	sphere->pos.z = -200;
	sphere->radius = 150;
}

void			set_sphere_color(t_com *com)
{
	com->color.r = 250;
	com->color.g = 190;
	com->color.b = 105;
	com->color.a = 0;
}

void			sphere_point_normalize(void *id, t_com *com)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)id;
	com->ray.n = subtract(&com->ray.intr, &sphere->pos, &com->ray.n);
	com->ray.n = scale(&com->ray.n, (1 / vec_len(&com->ray.n)));
}

void			sphere_intersect(void *id, t_vector pos, t_com *com, t_obj *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)id;
	com->dist = subtract(&pos, &sphere->pos, &com->dist);
	com->a = dot_prod(&com->ray.dir, &com->ray.dir);
	com->b = 2.0 * (dot_prod(&com->ray.dir, &com->dist));
	com->c = dot_prod(&com->dist, &com->dist) -
	(sphere->radius * sphere->radius);
	if (find_root(com) == 1)
	{
		if (equal(pos, com->cam.pos) == 0)
		{
			set_sphere_color(com);
			com->ray.intr = scale(&com->ray.dir, com->t);
			com->ray.intr = add(&pos, &com->ray.intr);
			sphere_point_normalize(obj->id, com);
		}
	}
}
