/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 18:26:26 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_obj		*create_plane(t_obj *obj, int nbr)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (nbr == 1)
		plane->num = 1;
	if (nbr == 2)
		plane->num = 2;
	if (nbr == 3)
		plane->num = 3;
	plane_param(plane);
	obj->id = (void*)(plane);
	obj->intersection = plane_intersect;
	return (obj);
}

void		plane_param(t_plane *plane)
{
	plane->normal.x = 0;
	plane->normal.y = 0;
	plane->normal.z = 0;
	if (plane->num == 1)
	{
		plane->pos.x = 0;
		plane->pos.y = 300;
		plane->pos.z = 400;
		plane->normal.z = -1;
	}
	if (plane->num == 2)
	{
		plane->pos.x = 100;
		plane->pos.y = 300;
		plane->pos.z = 0;
		plane->normal.x = 1;
	}
	if (plane->num == 3)
	{
		plane->pos.x = 400;
		plane->pos.y = 600;
		plane->pos.z = 100;
		plane->normal.y = -1;
	}
}

void		set_plane_color(t_plane *plane, t_com *com)
{
	if (plane->num == 1)
	{
		com->color.r = 164;
		com->color.g = 126;
		com->color.b = 113;
		com->color.a = 0;
	}
	if (plane->num == 2)
	{
		com->color.r = 230;
		com->color.g = 222;
		com->color.b = 168;
		com->color.a = 0;
	}
	if (plane->num == 3)
	{
		com->color.r = 170;
		com->color.g = 189;
		com->color.b = 199;
		com->color.a = 0;
	}
}

void		plane_point_normalize(void *id, t_com *com)
{
	t_plane	*plane;

	plane = (t_plane *)id;
	com->ray.n = plane->normal;
}

void		plane_intersect(void *id, t_vector pos, t_com *com, t_obj *obj)
{
	t_plane	*plane;

	plane = (t_plane *)id;
	com->a = dot_prod(&plane->normal, &com->ray.dir);
	com->b = dot_prod(&plane->normal, &pos);
	com->c = dot_prod(&plane->pos, &plane->normal);
	if (fabs(com->a) > 0.001)
	{
		com->t0 = (-(com->b - com->c) / com->a);
		if ((com->t0 > 0.1) && (com->t0 < com->t))
		{
			com->t = com->t0 - 0.01;
			if (equal(pos, com->cam.pos) == 0)
			{
				set_plane_color(plane, com);
				com->ray.intr = scale(&com->ray.dir, com->t);
				com->ray.intr = add(&pos, &com->ray.intr);
				plane_point_normalize(obj->id, com);
			}
		}
	}
}
