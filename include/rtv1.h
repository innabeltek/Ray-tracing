/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 17:16:11 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <pthread.h>
# include <unistd.h>
# include "../src/lib_vec/vector.h"

# define WIDTH 1600
# define HEIGHT 1200

typedef struct		s_plane
{
	t_vector		pos;
	t_vector		normal;
	int				num;
	double			dist;
}					t_plane;

typedef struct		s_sphere
{
	t_vector		pos;
	double			radius;
}					t_sphere;

typedef struct		s_cylinder
{
	t_vector		pos;
	t_vector		dir;
	double			radius;
}					t_cylinder;

typedef struct		s_cone
{
	t_vector		pos;
	t_vector		dir;
	double			angle;
}					t_cone;

typedef struct		s_light
{
	struct s_light	*next;
	t_vector		pos;
}					t_light;

typedef struct		s_img
{
	void			*mlx;
	void			*win;
	void			*image;
	char			*data;
	int				bpp;
	int				endian;
	int				size_line;
	int				num;
}					t_img;

typedef struct		s_camera
{
	t_vector		pos;
}					t_camera;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

typedef struct		s_ray
{
	t_vector		dir;
	t_vector		intr;
	t_vector		n;
}					t_ray;

typedef struct		s_obj
{
	struct s_obj	*next;
	void			*id;
	void			(*intersection)();
}					t_obj;

typedef struct		s_com
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			t0;
	double			t1;
	double			t;
	double			cos;
	t_camera		cam;
	t_vector		win;
	t_vector		dist;
	t_light			*light;
	t_color			color;
	t_ray			ray;
	t_obj			obj;
	t_img			*img;
}					t_com;

typedef struct		s_thread
{
	int				thread_num;
	t_obj			*obj;
	t_img			*img;
}					t_thread;

int					ft_strcmp(const char *s1, const char *s2);
void				error(void);

t_obj				*create_sphere(t_obj *obj);
t_obj				*create_plane(t_obj *obj, int nbr);
t_obj				*create_cone(t_obj *obj);
t_obj				*create_cylinder(t_obj *obj);

void				sphere_param(t_sphere *sphere);
void				plane_param(t_plane *plane);
void				cone_param(t_cone *cone);
void				cylinder_param(t_cylinder *cylinder);

void				light_param(t_com *com);
void				camera_position(t_com *com);

void				make_threads(t_img *img, t_obj *obj);

void				tracer(t_obj *obj, t_thread *flow, t_com *com);

void				sphere_intersect(void *id, t_vector pos, t_com *com,
	t_obj *obj);
void				plane_intersect(void *id, t_vector pos, t_com *com,
	t_obj *obj);
void				cylinder_intersect(void *id, t_vector pos, t_com *com,
	t_obj *obj);
void				cone_intersect(void *id, t_vector pos, t_com *com,
	t_obj *obj);
int					find_root(t_com *com);

void				sphere_point_normalize(void *id, t_com *com);
void				cylinder_point_normalize(void *id, t_com *com);
void				cone_point_normalize(void *id, t_com *com);
void				plane_point_normalize(void *id, t_com *com);

void				highlight(t_com *com);
void				background(t_com *com);
void				color_pix(t_com *com);
int					key_press(int keycode, t_img *img);

#endif
