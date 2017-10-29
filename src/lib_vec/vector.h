/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/05/22 13:30:49 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdlib.h>

typedef struct	s_vector
{
	double x;
	double y;
	double z;
	double rez;
}				t_vector;

t_vector		subtract(t_vector *v1, t_vector *v2, t_vector *res);
t_vector		vec_dir(t_vector *v1, t_vector *v2, t_vector *res);
t_vector		add(t_vector *v1, t_vector *v2);
t_vector		scale(t_vector *v, double c);
double			dot_prod(t_vector *v1, t_vector *v2);
double			angle(t_vector *v1, t_vector *v2);
double			vec_len(t_vector *v);
int				equal(t_vector v1, t_vector v2);

#endif
