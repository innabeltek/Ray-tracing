/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 18:29:45 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		light_param(t_com *com)
{
	t_light *light;
	t_light *light2;

	light = (t_light*)malloc(sizeof(t_light));
	light->pos.x = 400;
	light->pos.y = 400;
	light->pos.z = -600;
	light2 = (t_light*)malloc(sizeof(t_light));
	light->next = light2;
	light2->pos.x = 600;
	light2->pos.y = 300;
	light2->pos.z = -1000;
	light2->next = NULL;
	com->light = light;
}

void		camera_position(t_com *com)
{
	com->cam.pos.x = 300;
	com->cam.pos.y = 300;
	com->cam.pos.z = -1000;
}
