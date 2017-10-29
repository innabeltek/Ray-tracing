/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/05/22 13:24:59 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		scale(t_vector *v, double c)
{
	t_vector	res;

	res.x = v->x * c;
	res.y = v->y * c;
	res.z = v->z * c;
	return (res);
}
