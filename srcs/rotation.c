/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 01:53:18 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:38:39 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	rotate_x(t_vector3 v, float angle)
{
	float py;

	py = v.y;
	v.y = py * cos(angle) + v.z * sin(angle);
	v.z = -py * sin(angle) + v.z * cos(angle);
	return (v);
}

t_vector3	rotate_y(t_vector3 v, float angle)
{
	float px;

	px = v.x;
	v.x = px * cos(angle) + v.z * sin(angle);
	v.z = -px * sin(angle) + v.z * cos(angle);
	return (v);
}

t_vector3	rotate_z(t_vector3 v, float angle)
{
	float px;
	float py;

	px = v.x;
	py = v.y;
	v.x = px * cos(angle) - py * sin(angle);
	v.y = px * sin(angle) + py * cos(angle);
	return (v);
}

t_vector3	rotate_vector(t_vector3 v, t_vector3 rot)
{
	v = rotate_y(v, rot.y);
	v = rotate_x(v, rot.x);
	v = rotate_z(v, rot.z);
	return (v);
}
