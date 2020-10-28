  
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
    
    dst = img.addr + (int)round(y * img.line_length + x * (img.bpp / 8));
    *(unsigned int*)dst = color;
}

t_rgb	get_rgb(int clr)
{
	t_rgb color;
 
	color.b = clr % 256;
	color.g = ((clr - color.b) / 256) % 256;
	color.r = ((clr - color.b) / (256 * 256)) - (color.g / 256);
	return (color);
}

void			little_endian_fill_int(unsigned char *dest, int value)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		dest[i] = (unsigned char)(value >> (8 * i));
		i++;
	}
}

unsigned char	*bmp_file_header(int filesize)
{
	unsigned char *f_header;

	f_header = (unsigned char *)ft_calloc(14, sizeof(unsigned char));
	f_header[0] = 'B';
	f_header[1] = 'M';
	little_endian_fill_int(&f_header[2], filesize);
	f_header[10] = 54;
	return (f_header);
}

unsigned char	*bmp_info_header(t_config config)
{
	unsigned char *i_header;

	i_header = (unsigned char *)ft_calloc(40, sizeof(unsigned char));
	i_header[0] = 40;
	little_endian_fill_int(&i_header[4], config.width);
	little_endian_fill_int(&i_header[8], config.height);
	i_header[12] = 1;
	i_header[14] = 24;
	little_endian_fill_int(&i_header[20], 4 * config.width * config.height);
	little_endian_fill_int(&i_header[24], 72 * (int)(39.375));
	little_endian_fill_int(&i_header[28], 72 * (int)(39.375));
	return (i_header);
}


int						save_bmp(const char *filename, t_config config, int *image)
{
	unsigned char	*color[3];
	unsigned	char	*header[2];
	int				x;
	int 				fd;
	int				y;

	header[0] = bmp_file_header(4 * config.width * config.height + 54);
	header[1] = bmp_info_header(config);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 777);
	write(fd, header[0], 14);
	free(header[0]);
	write(fd, header[1], 40);
	free(header[1]);
	y = config.height;
	while (y > 0)
	{
		x = config.width * y - config.width;
		while (x < config.width * y)
		{
			little_endian_fill_int((unsigned char *)color, image[x]);
			write(fd, color, 3);
			x++;
		}
		y--;
	}
	close(fd);
	return (1);
}
