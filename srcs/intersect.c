/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:52:47 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/25 02:15:16 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_hit		ft_sp_int_help(t_hit hit, t_sphere sphere, t_ray ray, float delta)
{
	hit.sol /= 2;
	hit.p = ft_get_point(ray, hit.sol);
	hit.normal = ft_normalize(ft_minus(sphere.center, hit.p));
	hit.ray = ray;
	hit.color = sphere.color;
	hit.hit = (delta > 0);
	hit.id = sphere.id;
	return (hit);
}

t_hit		ft_sp_intersect(t_ray ray, t_sphere sphere)
{
	t_vector3	vec;
	float		a;
	float		b;
	float		delta;
	t_hit		hit;

	vec = ft_minus(ray.p1, sphere.center);
	a = ft_dot(ray.p2, ray.p2);
	b = 2.0 * ft_dot(vec, ray.p2);
	delta = b * b - (4 * a * (ft_dot(vec, vec) -
			sphere.radius * sphere.radius));
	hit.hit = FALSE;
	if (delta > 0 && ((-b + sqrtf(delta)) || (-b - sqrtf(delta))))
	{
		hit.sol = -b - sqrtf(delta) / (2.0 * a);
		if (hit.sol > -b + sqrtf(delta) / (2.0 * a))
			hit.sol = -b + sqrtf(delta) / (2.0 * a);
		if (hit.sol < 0)
			return (hit);
		hit = ft_sp_int_help(hit, sphere, ray, delta);
	}
	return (hit);
}

t_hit		ft_pl_intersect(t_ray ray, t_plane pl)
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

t_square	ft_find_sq_points(t_square sq, t_vector3 x)
{
	t_vector3	v;
	t_vector3	u;
	float		r;

	r = sqrtf(powf(sq.size, 2) / 2);
	v = ft_cross(sq.n, x);
	v = ft_normalize(v);
	u = ft_normalize(ft_cross(v, sq.n));
	sq.p1 = ft_plus(sq.p, ft_multi(v, r));
	sq.p3 = ft_minus(sq.p, ft_multi(v, r));
	sq.p2 = ft_plus(sq.p, ft_multi(u, r));
	sq.p4 = ft_minus(sq.p, ft_multi(u, r));
	return (sq);
}

t_hit		ft_sq_intersect(t_ray ray, t_square sq)
{
	t_hit		hit;
	float		denom;

	hit.hit = FALSE;
	hit.normal = vector3(0, 0, 0);
	denom = ft_dot(sq.n, ray.p2);
	if (denom <= 1e-6)
	{
		denom = ft_dot(ft_reverse(sq.n), ray.p2);
		sq.n = ft_reverse(sq.n);
	}
	if (denom > 1e-6)
	{
		sq = ft_find_sq_points(sq, vector3(1, 1, 1));
		hit = ft_tr_intersect(ray, triangle(sq.p3, sq.p2, sq.p1, sq.color));
		if (hit.hit != TRUE)
			hit = ft_tr_intersect(ray, triangle(sq.p4, sq.p3, sq.p1, sq.color));
		hit.id = sq.id;
		hit.normal = sq.n;
		hit.p = ft_get_point(ray, hit.sol);
	}
	return (hit);
}
