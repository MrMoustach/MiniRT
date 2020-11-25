/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 23:38:53 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/25 02:10:19 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void				bit_shift(unsigned char *arr, int val)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		arr[i] = (unsigned char)(val >> (8 * i));
		i++;
	}
}

unsigned	char	*bmp_header(int size)
{
	unsigned char *header;

	header = (unsigned char *)ft_calloc(14, sizeof(unsigned char));
	header[0] = 'B';
	header[1] = 'M';
	bit_shift(&header[2], size);
	header[10] = 54;
	return (header);
}

unsigned	char	*bmp_info(t_config config)
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

char			*make_name(t_config config, int *image)
{
	char			*t;

	t = (char *)malloc(10);
	t[0] = 'a' + image[1];
	t[1] = 'a' + config.height%25;
	t[2] = 'a' + config.width%25;
	t[3] = 'a' + ((int) &config)%25;
	t[4] = 'a' + ((int) image)%25;
	t[5] = '.';
	t[6] = 'b';
	t[7] = 'm';
	t[8] = 'p';
	t[9] = '\0';
	return (t);
}

int					save_bmp(const char *name, t_config config, int *image)
{
	unsigned	char	*color[3];
	unsigned	char	*header[2];
	int					x;
	int					fd;
	int					y;

	header[0] = bmp_header(4 * config.width * config.height + 54);
	header[1] = bmp_info(config);
	name = (const char *)make_name(config, image);
	fd = open(name, O_CREAT | O_WRONLY, 777);
	free((void *)name);
	write(fd, header[0], 14);
	free(header[0]);
	write(fd, header[1], 40);
	free(header[1]);
	y = config.height + 1;
	while (y-- > 0)
	{
		x = config.width * y - config.width;
		while (x < config.width * y)
		{
			bit_shift((unsigned char *)color, image[x]);
			write(fd, color, 3);
			x++;
		}
	}
	return (close(fd));
}
