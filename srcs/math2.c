/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 01:54:58 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:29:54 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3		ft_normalize(t_vector3 v)
{
	float	mag;

	mag = ft_mag(v);
	if (mag == 0)
	{
		v.x = 0;
		v.y = 0;
		v.z = 0;
		return (v);
	}
	v.x = v.x / mag;
	v.y = v.y / mag;
	v.z = v.z / mag;
	return (v);
}

float			ft_mag(t_vector3 v)
{
	float mag;

	mag = (powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	mag = sqrtf(mag);
	return (ft_fabs(mag));
}

t_vector3		ft_reverse(t_vector3 v)
{
	v.x *= -1;
	v.y *= -1;
	v.z *= -1;
	return (v);
}

unsigned	int	ft_rgbtohex(t_rgb color)
{
	return ((color.r * 65536) + (color.g * 256) + color.b);
}

float			ft_fabs(float a)
{
	if (a > 0)
		return (a);
	return (-1 * a);
}
