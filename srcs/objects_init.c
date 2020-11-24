/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 01:42:33 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:30:00 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	sp.radius = radius / 2;
	sp.color = color;
	return (sp);
}

t_vector3	vector3(float x, float y, float z)
{
	t_vector3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_rgb		rgb(int x, int y, int z)
{
	t_rgb v;

	v.r = x;
	v.g = y;
	v.b = z;
	return (v);
}

t_cylinder	cylinder(t_vector3 c, t_vector3 n, t_vector3 v, t_rgb r)
{
	t_cylinder	cy;

	cy.c = c;
	cy.n = n;
	cy.r = v.x / 2;
	cy.h = v.y;
	cy.color = r;
	return (cy);
}
