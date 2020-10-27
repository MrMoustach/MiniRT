  
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

static void				create_bmp(unsigned char *buf, t_config config, const char *filename)
{
	int				fd;
	unsigned	char	*header[2];

	header[0] = bmp_file_header(4 * config.width * config.height + 54);
	header[1] = bmp_info_header(config);
	fd = open("./image.bmp", O_WRONLY | O_APPEND | O_CREAT, 777);
	write(fd, header[0], 14);
	free(header[0]);
	write(fd, header[1], 40);
	free(header[1]);
	write(fd, (char *)buf, 4 * config.width * config.height);
	close(fd);
	free(buf);
}



static void				fill_image(unsigned char *buf, int width_in_bytes,
	int col, int row, t_config config)
{
	t_rgb	rgb;
	int		color_int;
	int		*data;

	data = (int *)mlx_get_data_addr(img.img, &color_int, &color_int, &color_int);
	color_int = data[(config.width - row) * config.height + col];
	rgb = get_rgb(color_int);
	buf[row * width_in_bytes + col * 3 + 0] = rgb.b;
	buf[row * width_in_bytes + col * 3 + 1] = rgb.g;
	buf[row * width_in_bytes + col * 3 + 2] = rgb.r;
}

int						save_bmp(const char *filename, t_config config)
{
	int				col;
	int				row;
	unsigned char	*buf;

	buf = malloc(4 * config.width * config.height + 54);
	row = config.height - 1;
	while (row >= 0)
	{
		col = 0;
		while (col < config.width)
		{
			fill_image(buf, 4 * config.width * config.height + 54, col, row, config);
			col++;
		}
		row--;
	}
	create_bmp(buf, config, filename);
	return (1);
}
