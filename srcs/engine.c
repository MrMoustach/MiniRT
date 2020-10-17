/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 08:57:29 by iharchi           #+#    #+#             */
/*   Updated: 2020/03/10 16:30:14 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
t_cam   ft_get_cam(t_scene scene, int flag, t_vector3 mov, t_vector3 rot)
{
	t_cam		ret;
	t_list		*head;
	int			n;
	static	int	sc;
	
	if (flag)
	{
		sc++;
		sc %= scene.cam_count;
	}
	head = scene.cams;
	n = 0;
	while(head && n++ < sc)
		head = (*head).next;
	(*(t_cam *)(*head).content).ray.p1 = ft_plus((*(t_cam *)(*head).content).ray.p1, mov);
	(*(t_cam *)(*head).content).ray.p2 = ft_plus((*(t_cam *)(*head).content).ray.p2, rot);
	ret = *(t_cam *)(*head).content;
	return (ret);
}

t_hit	ft_intersections(t_scene scene,t_ray r)
{
	t_list	*objs;
	t_hit	hit;
	t_hit	ret;

	objs = scene.objects;
	ret.sol = 100000;
	while (objs)
	{
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

t_rgb	ft_shot_ray(t_scene scene, t_ray r)
{
	t_hit		hit;
	float		dot;
	float		sol;
	t_rgb		color;

	hit = ft_intersections(scene, r);
	
	if (hit.hit == TRUE)
		color = ft_calc_light(scene, hit);
	else
		color = rgb(0,0,0);
	return (color);
}

void    ft_render(t_scene scene, int flag,t_vector3 mov, t_vector3 rot)
{
	t_list  *head;
	t_cam   camera;
	int     i;
	int     j;
	t_rgb	pixel;
	t_ray	r;
	clock_t t;
	float tt;
	
	j = 0;
	t = clock();
	camera = ft_get_cam(scene, flag,mov, rot);
	while (j < scene.config.height)
	{
		i = 0;
		while (i < scene.config.width)
		{
			r.p1 = camera.ray.p1;
			r.p2.x = (2*(i + 0.5)/(float)scene.config.width  - 1)*tan(camera.fov/2.)*
						scene.config.width/(float)scene.config.height;
			r.p2.y = -(2*(j + 0.5)/(float)scene.config.height - 1)*tan(camera.fov/2.);
			r.p2.z = camera.ray.p2.z;
			r.p2 = ft_plus(r.p2,camera.ray.p2);
			r.p2 = ft_normalize(r.p2);
			pixel = ft_shot_ray(scene, r);
			put_pix(i, j, ft_rgbtohex(pixel));
			i++;
		}
		j++;
	}
	
	mlx_string_put(cnx, win, 50, 50, 0xffffff, "Camera id:");
	mlx_string_put(cnx, win, 150, 50, 0xffffff, ft_itoa(camera.id));
	mlx_string_put(cnx, win, 50, 70, 0xffffff, "Pos : (");
	mlx_string_put(cnx, win, 125, 70, 0xffffff, ft_itoa(camera.ray.p1.x));
	mlx_string_put(cnx, win, 160, 70, 0xffffff, ",");
	mlx_string_put(cnx, win, 170, 70, 0xffffff, ft_itoa(camera.ray.p1.y));
	mlx_string_put(cnx, win, 200, 70, 0xffffff, ",");
	mlx_string_put(cnx, win, 210, 70, 0xffffff, ft_itoa(camera.ray.p1.z));
	mlx_string_put(cnx, win, 250, 70, 0xffffff, ")");
	mlx_string_put(cnx, win, 50, 90, 0xffffff, "FOV :");
	mlx_string_put(cnx, win, 120, 90, 0xffffff, ft_itoa(camera.fov/(M_PI/180)));
	mlx_string_put(cnx, win, 50, 110, 0xffffff, "Rot : (");
	mlx_string_put(cnx, win, 125, 110, 0xffffff, ft_itoa(camera.ray.p2.x));
	mlx_string_put(cnx, win, 160, 110, 0xffffff, ",");
	mlx_string_put(cnx, win, 170, 110, 0xffffff, ft_itoa(camera.ray.p2.y));
	mlx_string_put(cnx, win, 200, 110, 0xffffff, ",");
	mlx_string_put(cnx, win, 210, 110, 0xffffff, ft_itoa(camera.ray.p2.z));
	mlx_string_put(cnx, win, 250, 110, 0xffffff, ")");
	t = clock() - t;
	tt = ((double)t)/CLOCKS_PER_SEC;
	printf("It took %f s to render this frame\n", tt);
}