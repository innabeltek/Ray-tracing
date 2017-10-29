/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/05/27 17:27:34 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	angle(t_vector *v1, t_vector *v2)
{
	return ((((dot_prod(v1, v2)) / (vec_len(v1) * vec_len(v2)))));
}
