/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 17:55:51 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_obj			*create_cylinder(t_obj *obj)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder_param(cylinder);
	obj->id = (void*)(cylinder);
	obj->intersection = cylinder_intersect;
	return (obj);
}

void			cylinder_param(t_cylinder *cylinder)
{
	cylinder->pos.x = 200;
	cylinder->pos.y = 800;
	cylinder->pos.z = -500;
	cylinder->dir.x = 0.2;
	cylinder->dir.y = -0.8;
	cylinder->dir.z = 0;
	cylinder->radius = 45;
}

void			set_cylinder_color(t_com *com)
{
	com->color.r = 4;
	com->color.g = 62;
	com->color.b = 109;
	com->color.a = 0;
}

void			cylinder_point_normalize(void *id, t_com *com)
{
	t_cylinder	*cylinder;
	double		x;
	t_vector	tmp;

	cylinder = (t_cylinder *)id;
	com->ray.n = subtract(&com->ray.intr, &cylinder->pos, &com->ray.n);
	x = dot_prod(&com->ray.n, &cylinder->dir);
	tmp = scale(&cylinder->dir, x);
	com->ray.n = subtract(&com->ray.n, &tmp, &com->ray.n);
	com->ray.n = scale(&com->ray.n, (1 / vec_len(&com->ray.n)));
}

void			cylinder_intersect(void *id, t_vector pos, t_com *com,
	t_obj *obj)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)id;
	cylinder->dir = scale(&cylinder->dir, (1 / vec_len(&cylinder->dir)));
	com->a = dot_prod(&com->ray.dir, &com->ray.dir) -
	pow(dot_prod(&com->ray.dir, &cylinder->dir), 2);
	subtract(&pos, &cylinder->pos, &com->dist);
	com->b = 2 * (dot_prod(&com->dist, &com->ray.dir) - (dot_prod(&com->ray.dir,
		&cylinder->dir) * dot_prod(&com->dist, &cylinder->dir)));
	com->c = dot_prod(&com->dist, &com->dist) -
	pow(dot_prod(&com->dist, &cylinder->dir), 2) - (cylinder->radius *
		cylinder->radius);
	if (find_root(com) == 1)
	{
		if (equal(pos, com->cam.pos) == 0)
		{
			set_cylinder_color(com);
			com->ray.intr = scale(&com->ray.dir, com->t);
			com->ray.intr = add(&pos, &com->ray.intr);
			cylinder_point_normalize(obj->id, com);
		}
	}
}
