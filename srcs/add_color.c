/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 14:15:49 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:28:50 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_rgb		add_color(t_rgb c1, t_rgb c2)
{
	return ((t_rgb){clamp(0, c1.r + c2.r, 255),
			clamp(0, c1.g + c2.g, 255),
			clamp(0, c1.b + c2.b, 255)});
}

t_rgb		clamp_color(t_rgb v)
{
	return ((t_rgb){clamp(0, v.r, 255),
			clamp(0, v.g, 255),
			clamp(0, v.b, 255)});
}

t_rgb		rgb_multi(t_rgb rgb, float f)
{
	return ((t_rgb){clamp(0, rgb.r * f, 255),
			clamp(0, rgb.g * f, 255),
			clamp(0, rgb.b * f, 255)});
}
