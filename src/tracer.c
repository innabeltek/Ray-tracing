/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 18:31:52 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void			light_obj(t_obj *obj, t_com *com, t_vector inter,
	t_vector normal)
{
	double		a;

	com->t = 20000;
	subtract(&com->light->pos, &inter, &com->ray.dir);
	a = vec_len(&com->ray.dir);
	com->ray.dir = scale(&com->ray.dir, (1 / vec_len(&com->ray.dir)));
	while (obj)
	{
		obj->intersection(obj->id, inter, com, obj);
		if (com->t < 20000)
			break ;
		obj = obj->next;
	}
	com->cos = (angle(&com->ray.dir, &normal));
	if (com->t > a && com->cos > 0)
		highlight(com);
	else
		com->color.a += 230 / 2;
}

void			find_light(t_obj *obj, t_com *com)
{
	t_light		*light;

	light = com->light;
	while (com->light)
	{
		light_obj(obj, com, com->ray.intr, com->ray.n);
		com->light = com->light->next;
	}
	com->light = light;
}

void			tracer(t_obj *obj, t_thread *flow, t_com *com)
{
	t_obj		*begin;

	begin = obj;
	com->win.y = flow->thread_num;
	while (com->win.y < HEIGHT)
	{
		com->win.x = -1;
		while (++com->win.x < WIDTH)
		{
			com->t = 20000;
			subtract(&com->win, &com->cam.pos, &com->ray.dir);
			com->ray.dir = scale(&com->ray.dir, (1 / vec_len(&com->ray.dir)));
			while (obj)
			{
				obj->intersection(obj->id, com->cam.pos, com, obj);
				obj = obj->next;
			}
			obj = begin;
			com->t < 20000 ? find_light(obj, com) : background(com);
			color_pix(com);
		}
		com->win.y += flow->img->num - 1;
	}
}

void			*launch_intersect(void *thread_elem)
{
	t_thread	*flow;
	t_com		com;

	light_param(&com);
	camera_position(&com);
	flow = (t_thread*)thread_elem;
	com.img = (flow->img);
	tracer(flow->obj, flow, &com);
	return (NULL);
}

void			make_threads(t_img *img, t_obj *obj)
{
	int			i;
	pthread_t	*thread;
	t_thread	*flows;

	i = -1;
	img->num = 4;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * (img->num));
	flows = (t_thread *)malloc(sizeof(t_thread) * (img->num));
	while (++i < img->num)
	{
		flows[i].img = img;
		flows[i].obj = obj;
		flows[i].thread_num = i;
		pthread_create(&thread[i], NULL, launch_intersect, (void*)&flows[i]);
	}
	i = -1;
	while (++i < img->num)
		pthread_join(thread[i], NULL);
}
