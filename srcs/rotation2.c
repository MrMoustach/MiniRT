/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 03:41:25 by iharchi           #+#    #+#             */
/*   Updated: 2020/12/01 03:44:15 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	get_rotation(t_vector3 v)
{
	t_vector3	tmp;
	t_vector3	rot;

	tmp = ft_normalize(v);
	tmp.x = 0.0;
	rot.x = acos(ft_dot(vector3(0, 1, 0), ft_normalize(tmp)));
	tmp = ft_normalize(v);
	tmp.z = 0;
	rot.z = acos(ft_dot(vector3(0, 1, 0), ft_normalize(tmp)));
	rot.y = 0;
	return (rot);
}
