/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 20:43:56 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:29:49 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float		ft_dot(t_vector3 v1, t_vector3 v2)
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
