/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 08:57:29 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:29:02 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_cam			ft_get_cam(t_scene scene, int flag, t_vector3 mov,
t_vector3 rot)
{
	t_cam		ret;
	t_list		*head;
	int			n;
	static int	sc;

	if (flag)
	{
		sc++;
		sc %= scene.cam_count;
	}
	head = scene.cams;
	n = 0;
	while (head && n++ < sc)
		head = (*head).next;
	(*(t_cam *)(*head).content).ray.p1 =
		ft_plus((*(t_cam *)(*head).content).ray.p1, mov);
	(*(t_cam *)(*head).content).ray.p2 =
		ft_plus((*(t_cam *)(*head).content).ray.p2, rot);
	ret = *(t_cam *)(*head).content;
	return (ret);
}

t_hit			ft_intersections2(t_hit ret, t_list *objs, t_ray r,
						t_scene scene)
{
	t_hit hit;

	if ((*(t_object *)(*objs).content).type == 4)
	{
		hit = ft_sp_intersect(r, (*(t_object *)(*objs).content).sp);
		if (hit.hit && hit.sol < ret.sol)
			ret = hit;
	}
	if ((*(t_object *)(*objs).content).type == 5)
	{
		hit = ft_pl_intersect(r, (*(t_object *)(*objs).content).plane);
		if (hit.hit && hit.sol < ret.sol)
			ret = hit;
	}
	if ((*(t_object *)(*objs).content).type == 6)
	{
		hit = ft_sq_intersect(r, (*(t_object *)(*objs).content).square,
							scene);
		if (hit.hit && hit.sol < ret.sol)
			ret = hit;
	}
	return (ret);
}

t_hit			ft_intersections(t_scene scene, t_ray r)
{
	t_list	*objs;
	t_hit	hit;
	t_hit	ret;

	objs = scene.objects;
	ret.sol = 100000;
	while (objs)
	{
		ret = ft_intersections2(ret, objs, r, scene);
		if ((*(t_object *)(*objs).content).type == 7)
		{
			hit = ft_cy_intersect(r, (*(t_object *)(*objs).content).cylinder);
			if (hit.hit && hit.sol < ret.sol)
				ret = hit;
		}
		if ((*(t_object *)(*objs).content).type == 8)
		{
			hit = ft_tr_intersect(r, (*(t_object *)(*objs).content).triangle);
			if (hit.hit && hit.sol < ret.sol)
				ret = hit;
		}
		objs = (*objs).next;
	}
	return (ret);
}

unsigned int	ft_shot_ray(t_scene scene, t_ray r)
{
	t_hit			hit;
	float			dot;
	float			ol;
	unsigned int	color;

	hit = ft_intersections(scene, r);
	if (hit.hit == TRUE)
		color = ft_rgbtohex(ft_calc_light(scene, hit));
	else
		color = 0x01ffffff * scene.skybox;
	return (color);
}

void			ft_render(t_scene scene, int flag, t_vector3 mov, t_vector3 rot)
{
	t_list	*head;
	t_cam	camera;
	int		i;
	int		j;
	t_ray	r;

	j = 0;
	camera = ft_get_cam(scene, flag, mov, rot);
	while (j < scene.config.height)
	{
		i = 0;
		while (i < scene.config.width)
		{
			r = make_ray(scene, camera, i, j);
			put_pix(i, j, ft_shot_ray(scene, r), scene.skybox);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(g_cnx, g_win, g_img.img, 0, 0);
}
