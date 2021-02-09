/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:21:57 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/05 08:23:00 by iharchi          ###   ########.fr       */
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
		(*(t_light *)(*head).content).bright * (max(ft_dot(hp, hit.normal),
		0))));
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

t_rgb		get_uv_pattern(t_tuple uv, int h, int w)
{
	t_tuple	uv2;

	uv2.u = floor(uv.u * h);
	uv2.v = floor(uv.v * w);
	if (fmod(uv2.u + uv2.v, 2) == 0)
		return (rgb(0, 0, 0));
	return (rgb(255, 255, 255));
}
// TODO : FIX
t_rgb		get_uv_map(t_tuple uv)
{
	t_tuple			uv2;
	t_rgb 			ret;
	int				c;

	uv2.u = floor(uv.u * g_uvmap.width);
	uv2.v = floor(uv.v * g_uvmap.height);
	c = *(int *)(g_uvmap.addr + (int)round(uv2.v * g_uvmap.line_length + uv2.u *
											(g_uvmap.bpp / 8)));
	// printf("%x\n", *c);
	ret.r = (int)((int)c >> 16);
	ret.g = (int)(((int)c & 0x00ff00) >> 8);
	ret.b = (int)((int)c & 0x0000ff);
	// printf("%d %d %d \n", ret.r, ret.g, ret.b);
	return (ret);
}

t_tuple		get_spherical_cords(t_vector3 p, t_sphere sp)
{
	float		theta;
	float		phi;
	float		raw_u;
	t_tuple		uv;
	t_vector3	p2;

	p2 = ft_minus(p , sp.center);
	theta = atan2(p2.x, p2.z);
	phi = acos(p2.y / sp.radius);
	raw_u = theta / (2 * M_PI);
	uv.u = 1 - (raw_u + 0.5);
	uv.v = phi / M_PI;
	return (uv);
}

t_tuple		get_planar_cords(t_vector3 p, t_plane plane)
{
	t_tuple	uv;
	t_vector3	p2;

	p2 = ft_minus(p , plane.p);
	uv.u = fabs(fmod(p2.x, 1));
	uv.v = fabs(fmod(p2.z, 1));
	return (uv);
}

t_tuple		get_cylindrical_cords(t_vector3 p, t_cylinder cy)
{
	float	theta;
	float	raw_u;
	t_tuple	uv;
	t_vector3	p2;

	p2 = ft_minus(p , cy.c);
	theta = atan2(p2.x, p2.z);
	raw_u = theta / (2 * M_PI);
	uv.u = 1 - (raw_u + 0.5);
	uv.v = fmod(p2.y, 1);
	return (uv);
}

