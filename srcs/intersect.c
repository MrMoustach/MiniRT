/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:52:47 by iharchi           #+#    #+#             */
/*   Updated: 2020/10/24 02:08:45 by iharchi          ###   ########.fr       */
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

/*

v = cross(cam.p2, n) 
u = cross(v,n)
v = norm(v)
u = norm(u)
r = sqrt(pow(d)/2)
p1 = c + r*v
p2 = c - r*v
p3 = c + r*u
p4 = c - r*u
*/

t_square	ft_find_sq_points(t_square sq, t_vector3 x)
{
	t_vector3	v;
	t_vector3	u;
	float		r;

	//(void) x;
	r = sqrtf(powf(sq.size, 2) / 2);
	v = ft_cross(vector3(round(sq.n.x * -1), round(sq.n.y * -1), round(sq.n.z * -1)), sq.n);
	u = ft_normalize(ft_cross(v, sq.n));
	v = ft_normalize(v);
	sq.p1 = ft_plus(sq.p,ft_multi(v, r));
	sq.p3 = ft_minus(sq.p,ft_multi(v, r));
	sq.p2 = ft_plus(sq.p,ft_multi(u, r));
	sq.p4 = ft_minus(sq.p,ft_multi(u, r));
	return (sq);
}

t_hit	ft_sq_intersect(t_ray ray, t_square sq, t_scene scene)
{
	t_hit		hit;
	float		denom;

	hit.hit = FALSE;
	hit.normal = vector3(0, 0, 0);
	denom = ft_dot(sq.n, ray.p2);
	if (denom > 1e-6)
	{	
		t_cam cam1= ft_get_cam(scene, 0,vector3(0, 0, 0), vector3(0, 0, 0));
		sq = ft_find_sq_points(sq, cam1.ray.p2);
		hit = ft_tr_intersect(ray, triangle(sq.p1, sq.p3, sq.p2, sq.color));
		if (!hit.hit)
			hit = ft_tr_intersect(ray, triangle(sq.p1, sq.p4, sq.p3, sq.color));
		hit.normal = sq.n;
	}
	return (hit);
}

t_vector3	rotation_cy(t_cylinder cy)
{
	t_vector3	tmp;
	t_vector3	rot;

	tmp = cy.n;
	tmp.x = 0;
	rot.x = acos(ft_dot(vector3(0, 1, 0), ft_normalize(tmp)));
	tmp = cy.n;
	tmp.z = 0;
	rot.z = acos(ft_dot(vector3(0, 1, 0), ft_normalize(tmp)));
	rot.y = 0;
	return (rot);
}

t_hit ft_cy_intersect(t_ray ray, t_cylinder cy)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_hit	hit;
	t_vector3	pos;
	t_vector3	rot;
	static bool debug1 = FALSE;
	static bool debug2 = FALSE;

	// //rot = rotation_cy(cy);
	// if(!debug1)
	// {	
	// 	printf("rot : %f %f %f\n",rot.x, rot.y, rot.z, debug1 = TRUE);
	// 	printf("before : %f %f %f\n",ray.p2.x, ray.p2.y, ray.p2.z);
	// }
	
	// //ray.p1 = rotate_vector(ray.p1, ft_multi(rot, -1));
	// //ray.p2 = rotate_vector(ray.p2, ft_multi(rot, -1));
	
	// if(!debug2)
	// {	
	// 	printf("after : %f %f %f\n",ray.p2.x, ray.p2.y, ray.p2.z);
	// 	debug2 = TRUE;
	// }
	pos = ft_minus(ray.p1, cy.c);
	a = (ray.p2.x * ray.p2.x) + (ray.p2.z * ray.p2.z);
	b = 2 * ((pos.x * ray.p2.x) + (pos.z * ray.p2.z));
	c = (pos.x * pos.x) + (pos.z * pos.z) - cy.r * cy.r;
	delta = b * b - 4 * a * c;
	hit.hit = FALSE;
	if (delta > 0)
	{
		//printf("before : %f %f %f\n",rot.x, rot.y, rot.z);
		hit.sol = -b + sqrtf(delta) / (2.0 * a);
		if (hit.sol > -b - sqrtf(delta) / (2.0 * a))
			hit.sol = -b - sqrtf(delta) / (2.0 * a);
		if (hit.sol < 0)
			return (hit);
		hit.sol /= 2;
		hit.p = ft_get_point(ray, hit.sol);
			//printf("%f %f %f\n",hit.p.x, hit.p.y, hit.p.z);
		if ((hit.p.y > cy.c.y) && (hit.p.y < cy.c.y + cy.h))
		{
			hit.hit = TRUE;
			hit.normal = ft_normalize(ft_minus(vector3(cy.c.x, cy.c.y + cy.h / 2 , cy.c.z), hit.p));
			//hit.normal = rotate_vector(hit.normal, ft_multi(rot, 1 ));
			// hit.normal = ft_normalize(ft_minus(cy.c, hit.p));
			hit.id = cy.id;
			hit.ray = ray;
			hit.color = cy.color;
			//printf("%d %d %d\n",hit.color.r, hit.color.g, hit.color.b);
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
	hit.normal = ft_normalize(ft_cross(edge1, edge2));
	a = ft_dot(hit.normal, ray.p2);
	if (a <= 1e-6)
		ft_reverse(&(hit.normal));
	hit.color = tr.color;
	hit.ray = ray;
	hit.id = tr.id;
	hit.p = ft_get_point(ray, hit.sol);
	return (hit);
}
