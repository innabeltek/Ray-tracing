/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/03 17:19:30 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_obj			*create_cone(t_obj *obj)
{
	t_cone		*cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	cone_param(cone);
	obj->id = (void*)(cone);
	obj->intersection = cone_intersect;
	return (obj);
}

void			cone_param(t_cone *cone)
{
	cone->pos.x = 800;
	cone->pos.y = 300;
	cone->pos.z = -500;
	cone->dir.x = 0;
	cone->dir.y = 1;
	cone->dir.z = 0;
	cone->angle = 10 * (M_PI / 180);
}

void			set_cone_color(t_com *com)
{
	com->color.r = 0;
	com->color.g = 108;
	com->color.b = 125;
	com->color.a = 0;
}

void			cone_point_normalize(void *id, t_com *com)
{
	t_cone		*cone;
	double		x;
	t_vector	tmp;

	cone = (t_cone *)id;
	com->ray.n = subtract(&com->ray.intr, &cone->pos, &com->ray.n);
	x = dot_prod(&com->ray.n, &cone->dir);
	tmp = scale(&cone->dir, x);
	tmp = scale(&tmp, (1 + pow(tan(cone->angle), 2)));
	com->ray.n = subtract(&com->ray.n, &tmp, &com->ray.n);
	com->ray.n = scale(&com->ray.n, (1 / vec_len(&com->ray.n)));
}

void			cone_intersect(void *id, t_vector pos, t_com *com, t_obj *obj)
{
	t_cone		*cone;

	cone = (t_cone *)id;
	cone->dir = scale(&cone->dir, (1 / vec_len(&cone->dir)));
	com->a = dot_prod(&com->ray.dir, &com->ray.dir) - (1 +
		pow(tan(cone->angle), 2)) * pow(dot_prod(&com->ray.dir, &cone->dir), 2);
	com->dist = subtract(&pos, &cone->pos, &com->dist);
	com->b = 2 * (dot_prod(&com->ray.dir, &com->dist) - (1 -
		pow(tan(cone->angle), 2)) * (dot_prod(&com->ray.dir, &cone->dir) *
	dot_prod(&com->dist, &cone->dir)));
	com->c = dot_prod(&com->dist, &com->dist) - pow(dot_prod(&com->dist,
		&cone->dir), 2) * (1 + pow(tan(cone->angle), 2));
	com->d = (com->b * com->b) - 4.0 * com->a * com->c;
	if (find_root(com) == 1)
	{
		if (equal(pos, com->cam.pos) == 0)
		{
			set_cone_color(com);
			com->ray.intr = scale(&com->ray.dir, com->t);
			com->ray.intr = add(&pos, &com->ray.intr);
			cone_point_normalize(obj->id, com);
		}
	}
}
