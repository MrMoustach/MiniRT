/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 20:43:56 by iharchi           #+#    #+#             */
/*   Updated: 2020/10/19 01:05:35 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float   ft_dot(t_vector3 v1, t_vector3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector3	ft_minus(t_vector3 v1, t_vector3 v2)
{
	t_vector3 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vector3	ft_cross(t_vector3 v1, t_vector3 v2)
{
	t_vector3 ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vector3	ft_plus(t_vector3 v1, t_vector3 v2)
{
	t_vector3 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vector3	ft_multi(t_vector3 v, float d)
{
	t_vector3 v2;

	v2.x = v.x * d;
	v2.y = v.y * d;
	v2.z = v.z * d;
	return (v2);
}
t_vector3	ft_normalize(t_vector3	v)
{
	float	mag;

	mag = ft_mag(v);
	v.x = v.x / mag;
	v.y = v.y / mag;
	v.z = v.z / mag;
	return (v);
}
float	ft_mag(t_vector3 v)
{
	float mag;
	
	mag = (powf(v.x,2) + powf(v.y,2) + powf(v.z,2));
	mag = sqrtf(mag);
	if (mag < 0)
		printf("%f",mag);
	return (ft_abs(mag));
}
int		ft_reverse(t_vector3 *v)
{
	(*v).x *= -1;
	(*v).y *= -1;
	(*v).z *= -1;
	return (0);
}
unsigned	int		ft_rgbtohex(t_rgb color)
{
	return ((color.r * 65536) + (color.g * 256) + color.b);
}
int		ft_multiply(t_vector3 *v, float n)
{
	(*v).x *= n;
	(*v).y *= n;
	(*v).z *= n;
	return (255);
}
float	ft_abs(float a)
{
	if (a > 0)
		return (a);
	return (-1 * a);
}

float	clamp(float min, float val, float max)
{
	if (val >= min && val <= max)
		return (val);
	else if (val < min)
		return (min);
	else
		return (max);
}
t_vector3 sphere_normal(t_vector3 c, t_vector3 pi)
{
	return (ft_minus(pi, c));
}

int		ft_same_vector(t_vector3 v1, t_vector3 v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (TRUE);
	return (FALSE);
}