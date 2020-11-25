/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 23:38:53 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/25 04:14:02 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

char				*make_name(t_config config, int *image)
{
	char			*t;

	t = (char *)malloc(10);
	t[0] = 'a' + image[1] % 24;
	t[1] = 'a' + config.height % 24;
	t[2] = 'a' + config.width % 24;
	t[3] = 'a' + ((int)&config) % 24;
	t[4] = 'a' + ((int)image) % 24;
	t[5] = '.';
	t[6] = 'b';
	t[7] = 'm';
	t[8] = 'p';
	t[9] = '\0';
	return (t);
}

void				free_stuff(unsigned char **header, const char *name)
{
	free(header[0]);
	free(header[1]);
	free((void *)name);
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
	write(fd, header[0], 14);
	write(fd, header[1], 40);
	free_stuff(header, name);
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
