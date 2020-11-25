/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 03:55:43 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/25 02:17:15 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	get_rotation_cy(t_cylinder cy)
{
	t_vector3	tmp;
	t_vector3	rot;

	tmp = ft_normalize(cy.n);
	tmp.x = 0.0;
	rot.x = acos(ft_dot(vector3(0, 1, 0), ft_normalize(tmp)));
	tmp = ft_normalize(cy.n);
	tmp.z = 0;
	rot.z = acos(ft_dot(vector3(0, 1, 0), ft_normalize(tmp)));
	rot.y = 0;
	return (rot);
}

t_hit		ft_cy_int_help(t_vector3 solve, t_vector3 pos, t_ray ray,
t_cylinder cy)
{
	t_hit hit;

	hit.hit = FALSE;
	if (pos.x > 0)
	{
		hit.sol = -solve.y + sqrtf(pos.x) / (2.0 * solve.x);
		if (hit.sol > -solve.y - sqrtf(pos.x) / (2.0 * solve.x))
			hit.sol = -solve.y - sqrtf(pos.x) / (2.0 * solve.x);
		if (hit.sol < 0)
			return (hit);
		hit.sol /= 2;
		hit.p = ft_get_point(ray, hit.sol);
		if ((hit.p.y > cy.c.y) && (hit.p.y < cy.c.y + cy.h))
		{
			hit.hit = TRUE;
			hit.normal = ft_normalize(
					ft_minus(vector3(cy.c.x, hit.p.y, cy.c.z), hit.p));
			hit.id = cy.id;
			hit.ray = ray;
			hit.color = cy.color;
		}
	}
	return (hit);
}

t_hit		ft_cy_intersect(t_ray ray, t_cylinder cy)
{
	t_vector3	solve;
	t_vector3	pos;
	t_vector3	rot;
	t_vector3	offset;

	rot = get_rotation_cy(cy);
	ray.p1 = rotate_vector(ray.p1, ft_multi(rot, -1));
	ray.p2 = rotate_vector(ray.p2, ft_multi(rot, -1));
	offset = rotate_vector(cy.n, ft_multi(rot, -1));
	cy.c = rotate_vector(cy.c, ft_multi(rot, -1));
	cy.c = vector3(cy.c.x - (ft_fabs(offset.x) * cy.h / 2),
		cy.c.y - (ft_fabs(offset.y) * cy.h / 2), cy.c.z -
			(ft_fabs(offset.z) * cy.h / 2));
	pos = ft_minus(ray.p1, cy.c);
	solve.x = (ray.p2.x * ray.p2.x) + (ray.p2.z * ray.p2.z);
	solve.y = 2 * ((pos.x * ray.p2.x) + (pos.z * ray.p2.z));
	solve.z = (pos.x * pos.x) + (pos.z * pos.z) - cy.r * cy.r;
	pos.x = solve.y * solve.y - 4 * solve.x * solve.z;
	return (ft_cy_int_help(solve, pos, ray, cy));
}

t_hit		ft_tr_int_h(t_hit hit, t_ray ray, t_triangle tr, t_vector3 n)
{
	if (hit.sol > 0.001)
		hit.hit = TRUE;
	hit.normal = n;
	if (ft_dot(hit.normal, ray.p2) <= 1e-6)
		hit.normal = ft_reverse(hit.normal);
	hit.color = tr.color;
	hit.ray = ray;
	hit.id = tr.id;
	hit.p = ft_get_point(ray, hit.sol);
	return (hit);
}

t_hit		ft_tr_intersect(t_ray ray, t_triangle tr)
{
	t_vector3	edge1;
	t_hit		hit;
	float		f;
	float		u;
	t_vector3	q;

	edge1 = ft_minus(tr.p2, tr.p1);
	hit.normal = ft_cross(ray.p2, ft_minus(tr.p3, tr.p1));
	hit.hit = FALSE;
	if (ft_dot(edge1, hit.normal) < 0.0001 &&
		ft_dot(edge1, hit.normal) > -0.0001)
		return (hit);
	f = 1.0 / ft_dot(edge1, hit.normal);
	u = f * (ft_dot(ft_minus(ray.p1, tr.p1), hit.normal));
	if (u < 0 || u > 1)
		return (hit);
	q = ft_cross(ft_minus(ray.p1, tr.p1), edge1);
	if ((f * ft_dot(ray.p2, q)) < 0 ||
		u + (f * ft_dot(ray.p2, q)) > 1)
		return (hit);
	hit.sol = f * ft_dot(ft_minus(tr.p3, tr.p1), q);
	hit = ft_tr_int_h(hit, ray, tr,
		ft_normalize(ft_cross(edge1, ft_minus(tr.p3, tr.p1))));
	return (hit);
}
