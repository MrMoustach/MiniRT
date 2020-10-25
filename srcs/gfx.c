  
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

unsigned char	*bmp_info_header(int w, int h)
{
	unsigned char *i_header;

	i_header = (unsigned char *)ft_calloc(40, sizeof(unsigned char));
	i_header[0] = 40;
	little_endian_fill_int(&i_header[4], w);
	little_endian_fill_int(&i_header[8], h);
	i_header[12] = 1;
	i_header[14] = 24;
	little_endian_fill_int(&i_header[20], 4 * w * h);
	little_endian_fill_int(&i_header[24], 72 * (int)(39.375));
	little_endian_fill_int(&i_header[28], 72 * (int)(39.375));
	return (i_header);
}

int				save_bmp(const char *filename, t_config config, int *image)
{
	unsigned char	color[3];
	int				fd;
	unsigned char	*header[2];
	int				i;

	if ((fd = open(filename, O_CREAT | O_WRONLY)) < 0)
	{
		printf("Error opening file");
		return (0);
	}
	header[0] = bmp_file_header(4 * config.width * config.height + 54);
	header[1] = bmp_info_header(config.width, config.height);
	write(fd, header[0], 14);
	free(header[0]);
	write(fd, header[1], 40);
	free(header[1]);
	i = config.width * config.height - 1;
	while (i-- > 0)
	{
        //char *c = ft_strjoin("\n", ft_itoa(i));
        //write(0, c, 7);
		little_endian_fill_int((unsigned char *)color, image[i]);
		write(fd, color, 3);
	}
	close(fd);
	return (1);
}