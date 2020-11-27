/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 02:12:53 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/27 04:09:24 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	ft_is_direction_good(char **tab, int *err)
{
	t_vector3	v;

	v = ft_is_point_good(tab, err);
	if (err < 0)
		return (v);
	if (v.x == 0 && v.y == 0 && v.z == 0)
		return (vector3(*err = -1, 0, 0));
	return (ft_normalize(v));
}

t_rgb		ft_is_color_good(char **tab)
{
	int	r;
	int	g;
	int	b;

	if (!ft_string_is_int(tab[0]) || !ft_string_is_int(tab[1])
		|| !ft_string_is_int(tab[2]))
		return (rgb(-1, 0, 0));
	if (tab[3] != '\0')
		return (rgb(-1, 0, 0));
	r = ft_atoi(tab[0]);
	g = ft_atoi(tab[1]);
	b = ft_atoi(tab[2]);
	free_tab(tab);
	if (r < 0 || b < 0 || g < 0)
		return (rgb(-1, 0, 0));
	if (r > 255 || b > 255 || g > 255)
		return (rgb(-1, 0, 0));
	return (rgb(r, g, b));
}

t_ray		make_ray(t_scene scene, t_cam camera, float u, float v)
{
	t_ray		r;
	t_vector3	up;
	t_vector3	right;
	float		w;
	float		h;

	right = ft_normalize(ft_cross(camera.ray.p2, vector3(0, 1, 0)));
	up = ft_normalize(ft_cross(right, camera.ray.p2));
	h = tan(camera.fov / 2);
	w = h * (float)scene.config.width / (float)scene.config.height;
	r = camera.ray;
	r.p2 = ft_normalize(ft_plus(ft_plus(r.p2, ft_multi(right, u * w)),
			ft_multi(up, v * h)));
	return (r);
}
