/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 02:16:31 by iharchi           #+#    #+#             */
/*   Updated: 2020/10/19 17:45:30 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void put_pix(double x, double y, int color)
{
    char    *dst;
    
    //mlx_pixel_put(cnx, win, x, y,color);
    dst = img.addr + (int)round(y * img.line_length + x * (img.bpp / 8));
    *(unsigned int*)dst = color;
}