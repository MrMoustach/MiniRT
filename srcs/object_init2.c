/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 02:45:23 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:29:57 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light		light(t_vector3 pos, t_rgb color, float bright)
{
	t_light l;

	l.bright = bright;
	l.color = color;
	l.pos = pos;
	return (l);
}

t_ray		ray(t_vector3 p1, t_vector3 p2)
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

t_triangle	triangle(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_rgb co)
{
	t_triangle	tr;

	tr.p1 = v1;
	tr.p2 = v2;
	tr.p3 = v3;
	tr.color = co;
	return (tr);
}
