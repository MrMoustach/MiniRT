/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:10:41 by iharchi           #+#    #+#             */
/*   Updated: 2020/12/02 00:34:02 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void		ft_keys_to_cam(int key, t_scene *sc)
{
	t_scene scene;

	scene = *sc;
	if (key == KEY_C)
		ft_re_render(scene, 1, 0);
	else
		ft_re_render(scene, 0, key);
}

void		free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

t_config	ft_check_res(t_config config)
{
	if (config.width > 2560)
		config.width = 2560;
	if (config.height > 1320)
		config.height = 1440;
	return (config);
}

void		put_pix(double x, double y, int color, int sk)
{
	char	*dst;
	char	*src;

	dst = g_img.addr + (int)round(y * g_img.line_length + x * (g_img.bpp / 8));
	src = g_skybox.addr + (int)round(y * g_skybox.line_length + x *
											(g_skybox.bpp / 8));
	*(unsigned int*)dst = color;
	if (color == 0x01ffffff && sk)
	{
		*(unsigned int*)dst = *(unsigned int*)src;
	}
}

float		clamp(float min, float val, float max)
{
	if (val >= min && val <= max)
		return (val);
	else if (val < min)
		return (min);
	else
		return (max);
}
