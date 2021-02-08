/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 03:55:43 by iharchi           #+#    #+#             */
/*   Updated: 2020/12/01 04:27:42 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_hit		ft_disc_intersect(t_ray ray, t_cylinder cy)
{
	t_plane	pl;
	t_hit	hit;

	pl = plane(cy.c, cy.n, cy.color);
	hit = ft_pl_intersect(ray, pl);
	if (hit.hit == FALSE)
		pl = plane(ft_plus(cy.c,
			ft_multi(cy.n, cy.h)), ft_multi(cy.n, -1), cy.color);
	hit = ft_pl_intersect(ray, pl);
	if (sqrtf(ft_dot(ft_minus(hit.p, pl.p), ft_minus(hit.p, pl.p))) > cy.r)
		hit.hit = FALSE;
	hit.id = cy.id;
	return (hit);
}

t_hit		ft_cy_inte_h(t_hit hit, t_cylinder cy, t_ray ray, t_vector3 x)
{
	float	m;

	hit.p = ft_get_point(ray, hit.sol);
	m = ft_dot(ray.p2, cy.n) * hit.sol + ft_dot(x, cy.n);
	if (m >= 0 && m <= cy.h)
	{
		hit.hit = TRUE;
		hit.normal = ft_normalize(ft_minus(ft_minus(cy.c, hit.p),
						ft_multi(cy.n, -m)));
		hit.id = cy.id;
		hit.ray = ray;
		hit.color = get_uv_pattern(get_cylindrical_cords(hit.p, cy), 2, 2);
		// hit.color = cy.color;
	}
	else
		hit = ft_disc_intersect(ray, cy);
	return (hit);
}

t_hit		ft_cy_intersect(t_ray ray, t_cylinder cy)
{
	t_vector3	x;
	float		delta;
	t_vector3	solve;
	t_hit		hit;

	hit.hit = FALSE;
	x = ft_minus(ray.p1, cy.c);
	solve.x = ft_dot(ray.p2, ray.p2) - powf(ft_dot(ray.p2, cy.n), 2);
	solve.y = (2 * ft_dot(ray.p2, x)) - (2 * (ft_dot(ray.p2, cy.n) *
				ft_dot(x, cy.n)));
	solve.z = ft_dot(x, x) - powf(ft_dot(x, cy.n), 2) - cy.r * cy.r;
	delta = solve.y * solve.y - (4 * solve.x * solve.z);
	hit.sol = (-solve.y + sqrtf(delta)) / (2.0 * solve.x);
	if (hit.sol >= (-solve.y - sqrtf(delta)) / (2.0 * solve.x))
		hit.sol = (-solve.y - sqrtf(delta)) / (2.0 * solve.x);
	if (hit.sol < 0)
	{
		hit = ft_disc_intersect(ray, cy);
		return (hit);
	}
	if (delta >= 0)
		hit = ft_cy_inte_h(hit, cy, ray, x);
	return (hit);
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
