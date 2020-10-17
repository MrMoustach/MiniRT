/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:21:57 by iharchi           #+#    #+#             */
/*   Updated: 2020/03/08 14:21:06 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vector3	ft_get_point(t_ray ray, float sol)
{
	t_vector3	p;
	
	p.x = ray.p1.x + ray.p2.x * sol;
	p.y = ray.p1.y + ray.p2.y * sol;
	p.z = ray.p1.z + ray.p2.z * sol;
	return (p);
}
float	max(double n1, double n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}
int	ft_same(t_sphere sp1, t_sphere sp2)
{
	if (sp1.center.x == sp2.center.x && sp1.center.y == sp2.center.y && sp1.center.z == sp2.center.z && sp1.radius == sp2.radius)
		return (1);
	return (0);
}
t_rgb	ft_calc_light(t_scene scene, t_hit hit)
{
	t_vector3	hp;
	float		dot;
	t_rgb		color;
	t_list		*head;
	t_hit		soll;
	t_light		l;
	
	head = scene.lights;
	dot = 0;
	color = rgb(0,0,0);
	while (head)
	{
		l = (*(t_light *)(*head).content);
		hp = ft_minus(hit.p, l.pos);
		hp = ft_normalize(hp);
		soll = ft_intersections(scene, ray(hit.p, ft_multi(hp, -1)));
		// lol = 1;
		// if (soll.hit == TRUE)
		// 	if (soll.id != hit.id)
		// 		if (soll.sol < hit.sol)
		// 			lol = 0;
		dot += !(soll.hit == TRUE && soll.id != hit.id && soll.sol < hit.sol) * 
						l.bright *  (max(ft_dot(hp, hit.normal), 0));
		color = add_color(color, rgb_multi(l.color, l.bright));
		head = (*head).next;
	}
	color = add_color(add_color(rgb_multi(hit.color,scene.am.bright), 
			rgb_multi(scene.am.color,scene.am.bright)),add_color(rgb_multi(color, 
			(dot)),rgb_multi(hit.color, dot)));
	return (color);
}
t_square	square(t_vector3 p, t_vector3 n, float size, t_rgb c)
{
	t_square sq;

	sq.p = p;
	sq.n = n;
	sq.size = size;
	sq.color = c;
	return (sq);
}
t_sphere	sphere(t_vector3 center, float radius, t_rgb color)
{
	t_sphere sp;

	sp.center = center;
	sp.radius = radius/2;
	sp.color = color;
	return (sp);
}

t_vector3	vector3(float x, float y, float z)
{
	t_vector3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

t_rgb	rgb(int x, int y, int z)
{
	t_rgb v;

	v.r = x;
	v.g = y;
	v.b = z;
	return v;
}

t_light	light(t_vector3 pos, t_rgb color, float bright)
{
	t_light l;
	
	l.bright = bright;
	l.color = color;
	l.pos = pos;
	return (l);
}

t_ray	ray(t_vector3 p1, t_vector3 p2)
{
	t_ray r;

	r.p1 = p1;
	r.p2 = p2;
	return (r);
}
t_ambient	ambient(float bright, t_rgb color)
{
	t_ambient a;

	a.bright = bright;
	a.color = color;
	return (a);
}
t_plane		plane(t_vector3 p, t_vector3 n, t_rgb c)
{
	t_plane pl;

	pl.p = p;
	pl.n = n;
	pl.color = c;
	return (pl);
}

t_cylinder	cylinder(t_vector3 c, t_vector3 n, float d, float h, t_rgb r)
{
	t_cylinder	cy;

	cy.c = c;
	cy.n = n;
	cy.r = d / 2;
	cy.h = h;
	cy.color = r;
	return (cy);
}
t_triangle	triangle(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_rgb co)
{
	t_triangle	tr;
	
	tr.p1 = v1;
	tr.p2 = v2;
	tr.p3 = v3;
	tr.color = co;
	return (tr);
}
t_cam		cam(t_ray ray, int fov)
{
	t_cam	cam;

	cam.fov = fov * M_PI/180;
	cam.ray = ray;
	return (cam);
}