/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 16:05:05 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		color_pix(t_com *com)
{
	int		y;
	int		x;
	int		size;

	y = com->win.y;
	x = com->win.x;
	size = com->img->size_line;
	if ((x >= 0 && x <= WIDTH) && (y >= 0 && y <= HEIGHT))
	{
		(com->img->data)[(y * size) + (x * 4)] = com->color.b;
		(com->img->data)[(y * size) + ((x * 4) + 1)] = com->color.g;
		(com->img->data)[(y * size) + ((x * 4) + 2)] = com->color.r;
		(com->img->data)[(y * size) + ((x * 4) + 3)] = com->color.a;
	}
}

void		highlight(t_com *com)
{
	float	f;

	f = 0.9 * pow(com->cos, 20) + 0.1 * com->cos;
	com->color.a += (230 * (1 - com->cos) / 2);
	com->color.r += (255 - com->color.r) * f;
	com->color.g += (255 - com->color.g) * f;
	com->color.b += (255 - com->color.b) * f;
}

void		background(t_com *com)
{
	com->color.r = 225;
	com->color.g = 225;
	com->color.b = 225;
	com->color.a = 220;
}
