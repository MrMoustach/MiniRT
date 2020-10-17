/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:52:47 by iharchi           #+#    #+#             */
/*   Updated: 2020/03/10 16:36:24 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_hit	ft_sp_intersect(t_ray ray, t_sphere sphere)
{
	t_vector3	vec;
	float		a;
	float		b;
	float		c;
	float		delta;
	t_hit		hit;

	vec = ft_minus(ray.p1, sphere.center);
	a = ft_dot(ray.p2, ray.p2);
	b = 2.0 * ft_dot(vec, ray.p2);
	c = ft_dot(vec, vec) - sphere.radius * sphere.radius;
	delta = b * b - (4 * a * c);
	hit.hit = FALSE;
	if (delta > 0 && ((-b + sqrtf(delta)) || (-b - sqrtf(delta))))
	{
		hit.sol = -b - sqrtf(delta) / (2.0 * a);
		if (hit.sol > -b + sqrtf(delta) / (2.0 * a))
			hit.sol = -b + sqrtf(delta) / (2.0 * a);
		if (hit.sol < 0)
		{
			hit.hit = FALSE;
			return (hit);
		}
		hit.sol /= 2;
		hit.p = ft_get_point(ray, hit.sol);
		hit.normal = ft_normalize(ft_minus(sphere.center,hit.p));
		hit.ray = ray;
		hit.color = sphere.color;
		hit.hit = (delta > 0);
		hit.id = sphere.id;
	}

	return (hit);
}

t_hit	ft_pl_intersect(t_ray ray, t_plane pl)
{
	float		denom;
	t_vector3	tmp;
	t_hit		hit;

	hit.hit = FALSE;
	denom = ft_dot(pl.n, ray.p2);
	if (denom > 1e-6)
	{
		tmp = ft_minus(pl.p, ray.p1);
		hit.sol = ft_dot(tmp, pl.n) / denom;
		hit.hit = (hit.sol >= 0);
		hit.color = pl.color;
		hit.id = pl.id;
		hit.normal = pl.n;
		hit.p = ft_get_point(ray, hit.sol);
		hit.ray = ray;
	}
	return (hit);
}

t_hit	ft_sq_intersect(t_ray ray, t_square sq)
{
	float		denom;
	t_vector3	tmp;
	t_hit		hit;
	float		dist;

	hit.hit = FALSE;
	denom = ft_dot(sq.n, ray.p2);
	if (denom > 1e-6)
	{
		tmp = ft_minus(sq.p, ray.p1);
		hit.sol = ft_dot(tmp, sq.n) / denom;
		hit.p = ft_get_point(ray, hit.sol);
		dist = ft_mag(ft_minus(hit.p, sq.p));
		hit.hit = (hit.sol >= 0 && dist <= sq.size);
		hit.color = sq.color;
		hit.id = sq.id;
		hit.normal = sq.n;
		hit.ray = ray;
	}
	return (hit);
}

t_hit ft_cy_intersect(t_ray ray, t_cylinder cy)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_hit	hit;
	t_vector3	pos;

	pos = ft_minus(ray.p1, cy.c);
	a = (ray.p2.x * ray.p2.x) + (ray.p2.z * ray.p2.z);
	b = 2 * ((ray.p1.x * ray.p2.x) + (pos.z * ray.p2.z));
	c = (pos.x *pos.x) + (pos.z * pos.z) - cy.r * 2;
	delta = b * b - 4 * a * c;
	hit.hit = FALSE;
	if (delta > 0)
	{
		hit.sol = -b - sqrtf(delta) / (2.0 * a);
		if (hit.sol > -b + sqrtf(delta) / (2.0 * a))
			hit.sol = -b + sqrtf(delta) / (2.0 * a);
		if (hit.sol < 0)
			return (hit);
		hit.sol /= 2;
		hit.p = ft_get_point(ray, hit.sol);
		if ((hit.p.y > cy.c.y) && (hit.p.y < cy.c.y + cy.h))
		{
			hit.hit = TRUE;
			hit.normal = ft_normalize(ft_minus(vector3(cy.c.x, 0 , cy.c.z), hit.p));
			hit.id = cy.id;
			hit.ray = ray;
			hit.color = cy.color;
		}
	}
	return (hit);
}

t_hit	ft_tr_intersect(t_ray ray, t_triangle tr)
{
	t_vector3	edge1;
	t_vector3	edge2;
	t_hit		hit;
	float		a;
	float		f;
	float		v;
	float		u;
	t_vector3	s;
	t_vector3	q;

	edge1 = ft_minus(tr.p2, tr.p1);
	edge2 = ft_minus(tr.p3, tr.p1);
	hit.normal = ft_cross(ray.p2, edge2);
	hit.hit = FALSE;
	a = ft_dot(edge1, hit.normal);
	if (a < 0.0001 && a > -0.0001)
		return (hit);
	f = 1.0/a;
	s = ft_minus(ray.p1, tr.p1);
	u = f * (ft_dot(s, hit.normal));
	if (u < 0 || u > 1)
		return (hit);
	q = ft_cross(s, edge1);
	v = f * ft_dot(ray.p2, q);
	if (v < 0 || u + v > 1)
		return (hit);
	hit.sol = f * ft_dot(edge2, q);
	if (hit.sol > 0.001)
		hit.hit = TRUE;
	hit.normal = ft_normalize(hit.normal);
	hit.color = tr.color;
	hit.ray = ray;
	hit.id = tr.id;
	hit.p = ft_get_point(ray, hit.sol);
	return (hit);
}
