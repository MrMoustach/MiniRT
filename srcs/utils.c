/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:10:41 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/22 04:12:49 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void free_objs(t_object *obj)
{
    free(obj);
}

void		ft_keys_to_cam(int key, t_scene *sc)
{
	t_scene scene;

	scene = *sc;
	if (key == KEY_C)
		ft_re_render(scene, 1, vector3(0, 0, 0), vector3(0, 0, 0));
	if (key == KEY_UP)
		ft_re_render(scene, 0, vector3(0, 0, 1), vector3(0, 0, 0));
	if (key == KEY_DOWN)
		ft_re_render(scene, 0, vector3(0, 0, -1), vector3(0, 0, 0));
	if (key == KEY_LEFT)
		ft_re_render(scene, 0, vector3(-1, 0, 0), vector3(0, 0, 0));
	if (key == KEY_RIGHT)
		ft_re_render(scene, 0, vector3(1, 0, 0), vector3(0, 0, 0));
	if (key == KEY_U)
		ft_re_render(scene, 0, vector3(0, 1, 0), vector3(0, 0, 0));
	if (key == KEY_D)
		ft_re_render(scene, 0, vector3(0, -1, 0), vector3(0, 0, 0));
	if (key == KEY_2)
		ft_re_render(scene, 0, vector3(0, 0, 0), vector3(0, -0.1, 0));
	if (key == KEY_4)
		ft_re_render(scene, 0, vector3(0, 0, 0), vector3(-0.1, 0, 0));
	if (key == KEY_6)
		ft_re_render(scene, 0, vector3(0, 0, 0), vector3(0.1, 0, 0));
	if (key == KEY_8)
		ft_re_render(scene, 0, vector3(0, 0, 0), vector3(0, 0.1, 0));
}

int	checkSum_line(char *line)
{
	int type;
	char **tab;

	tab = ft_split(line, ' ');
	type = get_type(tab[0]);
	free_tab(tab);
	if(type < -1 || type > 8)
		return(-1);
	//ft_printf("%d %s\n",type,line);
	return (0);
}

void	free_tab(char **tab)
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
	if (config.height > 1440)
		config.height = 1440;
	return (config);
}
