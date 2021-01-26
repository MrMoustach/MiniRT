/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 08:57:29 by iharchi           #+#    #+#             */
/*   Updated: 2021/01/26 12:32:43 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_cam			ft_get_cam(t_scene scene, int flag, int key)
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
	ret = *(t_cam *)(*head).content;
	ret.ray.p1 = move_cam(ret, key);
	ret.ray.p2 = rotate_cam(ret, key);
	ret.right = ft_normalize(ft_cross(ret.ray.p2,
				ft_normalize(vector3(0, 1, -ret.ray.p2.y))));
	ret.up = ft_normalize(ft_cross(ret.right, ret.ray.p2));
	ret.h = tan(ret.fov / 2);
	ret.w = ret.h * (float)scene.config.width / (float)scene.config.height;
	*(t_cam *)(*head).content = ret;
	return (ret);
}

t_hit			ft_intersections2(t_hit ret, t_list *objs, t_ray r,
						t_scene scene)
{
	t_hit hit;

	(void)scene;
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
		hit = ft_sq_intersect(r, (*(t_object *)(*objs).content).square);
		if (hit.hit && hit.sol < ret.sol)
			ret = hit;
	}
	return (ret);
}

t_hit			ft_intersections(t_scene scene, t_ray r, float max)
{
	t_list	*objs;
	t_hit	hit;
	t_hit	ret;

	objs = scene.objects;
	ret.sol = max;
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
	unsigned int	color;

	hit = ft_intersections(scene, r, 100000);
	if (hit.hit == TRUE)
		color = ft_rgbtohex(ft_calc_light(scene, hit));
	else
		color = 0x01ffffff * scene.skybox;
	return (color);
}

void			ft_render(t_scene scene, int flag, int key)
{
	t_cam	camera;
	int		i;
	int		j;
	t_ray	r;
	
	i = 0;
	camera = ft_get_cam(scene, flag, key);
	while (i < scene.config.height)
	{
		j = 0;
		while (j < scene.config.width)
		{
			r = make_ray(scene, camera, (float)(-2 * j) /
			(float)(scene.config.width) + 1, (float)(-2 * i) /
			(float)(scene.config.height) + 1);
			unsigned int col = ft_shot_ray(scene, r);
			put_pix(j, i, col, scene.skybox);
			j++;
			if (!scene.ascii)
				printf("\rProgress : %f%%", ((float)(i * scene.config.height + j) / (float)(scene.config.width * scene.config.height)) * 100);
			else
			{
				int new_col = (((col - 0x0) * (8 - 0)) / (0xffffff - 0x0)) + 0x0;
				printf("\033[0;%dm  \033[0m", 40 + new_col);
			}
		}
		if (scene.ascii)
			printf("\n");
		i++;
	}
	mlx_put_image_to_window(g_cnx, g_win, g_img.img, 0, 0);
}
