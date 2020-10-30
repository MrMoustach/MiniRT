/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 23:38:53 by iharchi           #+#    #+#             */
/*   Updated: 2020/10/28 23:41:19 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void			bit_shift(unsigned char *arr, int val)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		arr[i] = (unsigned char)(val >> (8 * i));
		i++;
	}
}

unsigned char	*bmp_header(int size)
{
	unsigned char *header;

	header = (unsigned char *)ft_calloc(14, sizeof(unsigned char));
	header[0] = 'B';
	header[1] = 'M';
	bit_shift(&header[2], size);
	header[10] = 54;
	return (header);
}

unsigned char	*bmp_info(t_config config)
{
	unsigned char *info;

	info = (unsigned char *)ft_calloc(40, sizeof(unsigned char));
	info[0] = 40;
	bit_shift(&info[4], config.width);
	bit_shift(&info[8], config.height);
	info[12] = 1;
	info[14] = 24;
	bit_shift(&info[20], 4 * config.width * config.height);
	bit_shift(&info[24], 72 * (int)(39.375));
	bit_shift(&info[28], 72 * (int)(39.375));
	return (info);
}

int						save_bmp(const char *name, t_config config, int *image)
{
	unsigned char	*color[3];
	unsigned	char	*header[2];
	int				x;
	int 				fd;
	int				y;

	header[0] = bmp_header(4 * config.width * config.height + 54);
	header[1] = bmp_info(config);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 777);
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
			bit_shift((unsigned char *)color, image[x]);
			write(fd, color, 3);
			x++;
		}
		y--;
	}
	close(fd);
	return (1);
}
