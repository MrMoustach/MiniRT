/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:21:57 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/27 02:26:49 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	ft_get_point(t_ray ray, float sol)
{
	t_vector3	p;

	p.x = ray.p1.x + ray.p2.x * sol;
	p.y = ray.p1.y + ray.p2.y * sol;
	p.z = ray.p1.z + ray.p2.z * sol;
	return (p);
}

float		max(double n1, double n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

t_rgb		ft_calc_light(t_scene scene, t_hit hit)
{
	t_vector3	hp;
	float		dot;
	t_rgb		color;
	t_list		*head;
	t_hit		soll;

	head = scene.lights;
	dot = 0;
	color = rgb(0, 0, 0);
	while (head)
	{
		hp = ft_normalize(ft_minus(hit.p, (*(t_light *)(*head).content).pos));
		soll = ft_intersections(scene, ray(hit.p, ft_multi(hp, -1)), 100000);
		dot += !(soll.hit == TRUE && soll.id != hit.id && soll.sol < hit.sol) *
						(*(t_light *)(*head).content).bright *
						(max(ft_dot(hp, hit.normal), 0));
		color = add_color(color, rgb_multi((*(t_light *)(*head).content).color,
		(*(t_light *)(*head).content).bright * (max(ft_dot(hp, hit.normal), 0))));
		head = (*head).next;
	}
	color = add_color(add_color(rgb_multi(hit.color, scene.am.bright),
			rgb_multi(scene.am.color, scene.am.bright)),
			add_color(color, rgb_multi(hit.color, dot)));
	return (color);
}

t_cam		cam(t_ray ray, int fov)
{
	t_cam	cam;

	cam.fov = fov * M_PI / 180;
	cam.ray = ray;
	return (cam);
}
