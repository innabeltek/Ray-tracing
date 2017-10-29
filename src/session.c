/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:15:59 by ibeltek           #+#    #+#             */
/*   Updated: 2017/07/04 16:05:05 by ibeltek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		open_session(t_obj *obj)
{
	t_img	*img;

	img = (t_img*)malloc(sizeof(t_img));
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, WIDTH, HEIGHT, "new_win");
	img->image = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->bpp = 32;
	img->endian = 0;
	img->data = mlx_get_data_addr(img->image, &img->bpp,
		&img->size_line, &img->endian);
	make_threads(img, obj);
	mlx_put_image_to_window(img->mlx, img->win, img->image, 0, 0);
	mlx_destroy_image(img->mlx, img->image);
	mlx_hook(img->win, 2, 5, key_press, &img);
	mlx_loop(img->mlx);
}

t_obj		*new_elem(char *obj_name)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (ft_strcmp(obj_name, "sphere") == 0)
		obj = create_sphere(obj);
	else if (ft_strcmp(obj_name, "plane") == 0)
		obj = create_plane(obj, 1);
	else if (ft_strcmp(obj_name, "plane2") == 0)
		obj = create_plane(obj, 2);
	else if (ft_strcmp(obj_name, "plane3") == 0)
		obj = create_plane(obj, 3);
	else if (ft_strcmp(obj_name, "cone") == 0)
		obj = create_cone(obj);
	else if (ft_strcmp(obj_name, "cylinder") == 0)
		obj = create_cylinder(obj);
	else
		error();
	obj->next = NULL;
	return (obj);
}

t_obj		*create_scene(t_obj *obj)
{
	t_obj	*tmp;

	obj = new_elem("sphere");
	tmp = new_elem("cone");
	obj->next = tmp;
	tmp->next = new_elem("cylinder");
	tmp = tmp->next;
	tmp->next = new_elem("plane");
	tmp = tmp->next;
	tmp->next = new_elem("plane2");
	tmp = tmp->next;
	tmp->next = new_elem("plane3");
	return (obj);
}

t_obj		*create_lst(t_obj *obj, char **av, int i, int ac)
{
	t_obj	*tmp;

	tmp = new_elem(av[i]);
	obj->next = tmp;
	while (++i <= (ac - 1))
	{
		tmp->next = new_elem(av[i]);
		tmp = tmp->next;
	}
	return (obj);
}

int			main(int ac, char **av)
{
	int		i;
	t_obj	*obj;

	i = 0;
	obj = NULL;
	if (ac == 2 && ft_strcmp(av[1], "scene") == 0)
		obj = create_scene(obj);
	else if (ac >= 2)
	{
		obj = new_elem(av[++i]);
		if (av[++i])
			obj = create_lst(obj, av, i, ac);
	}
	else
		error();
	open_session(obj);
	return (0);
}
