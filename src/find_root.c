/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 17:55:51 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int	find_root(t_com *com)
{
	com->d = (com->b * com->b) - 4.0 * com->a * com->c;
	if (com->d > 0)
	{
		com->t0 = -(com->b - sqrtf(com->d)) / (2 * com->a);
		com->t1 = -(com->b + sqrtf(com->d)) / (2 * com->a);
		com->t0 = com->t0 < 0 ? 2000000 : com->t0;
		com->t1 = com->t1 < 0 ? 2000000 : com->t1;
		com->t0 = com->t0 > com->t1 ? com->t1 : com->t0;
		if ((com->t0 > 0.1) && (com->t0 < com->t))
		{
			com->t = com->t0 - 1;
			return (1);
		}
	}
	return (0);
}
