/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 03:41:25 by iharchi           #+#    #+#             */
/*   Updated: 2020/12/02 00:34:21 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	get_rotation(t_vector3 v, t_vector3 ref)
{
	t_vector3	tmp;
	t_vector3	rot;

	tmp = ft_normalize(v);
	tmp.x = 0.0;
	rot.x = acos(ft_dot(ref, ft_normalize(tmp)));
	tmp = ft_normalize(v);
	tmp.z = 0;
	rot.z = acos(ft_dot(ref, ft_normalize(tmp)));
	rot.y = 0;
	return (rot);
}

t_vector3	move_cam(t_cam cam, int key)
{
	if (key == KEY_UP)
		return (ft_plus(cam.ray.p1, cam.ray.p2));
	if (key == KEY_DOWN)
		return (ft_plus(cam.ray.p1, ft_multi(cam.ray.p2, -1)));
	if (key == KEY_LEFT)
		return (ft_plus(cam.ray.p1, cam.right));
	if (key == KEY_RIGHT)
		return (ft_plus(cam.ray.p1, ft_multi(cam.right, -1)));
	if (key == KEY_U)
		return (ft_plus(cam.ray.p1, cam.up));
	if (key == KEY_D)
		return (ft_plus(cam.ray.p1, ft_multi(cam.up, -1)));
	return (cam.ray.p1);
}

t_vector3	rotate_cam(t_cam cam, int key)
{
	if (key == KEY_8)
		return (ft_normalize(ft_plus(cam.ray.p2, ft_multi(cam.up, 0.1))));
	if (key == KEY_2)
		return (ft_normalize(ft_plus(cam.ray.p2, ft_multi(cam.up, -0.1))));
	if (key == KEY_4)
		return (ft_normalize(ft_plus(cam.ray.p2, ft_multi(cam.right, 0.1))));
	if (key == KEY_6)
		return (ft_normalize(ft_plus(cam.ray.p2, ft_multi(cam.right, -0.1))));
	return (cam.ray.p2);
}
