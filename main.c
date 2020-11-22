/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:50:13 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/22 01:28:00 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		ft_re_render(t_scene scene, int flag, t_vector3 mov, t_vector3 rot)
{
	mlx_destroy_image(cnx, img.img);
	img.img = mlx_new_image(cnx, scene.config.width, scene.config.height);
	img.addr = mlx_get_data_addr(img.img,
								&img.bpp, &img.line_length, &img.endian);
	ft_render(scene, flag, mov, rot);
}

int			keys(int key, void *param)
{
	t_scene	scene;

	scene = *((t_scene *)param);
	if (key == KEY_ESC)
		close_win(0, param);
	ft_keys_to_cam(key, &scene);
	return (0);
}

int			close_win(int key, void *param)
{
	t_scene scene;

	scene = *(t_scene*)param;
	ft_lstclear(&(scene.objects), free);
	(void)key;
	exit(EXIT_SUCCESS);
	return (1);
}

t_scene		argument_handler(t_scene scene, char **argv, int argc)
{
	scene.err_code = 0;
	scene.save = 0;
	if (argc > 3 || argc < 2)
	{
		scene.err_code = -4;
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 10) == 0)
			scene.save = 1;
		else
			scene.err_code = -3;
	}
	if (scene.err_code == 0)
		scene = ft_parse(scene, argv[1]);
	return (scene);
}

int			main(int argc, char *argv[])
{
	t_scene scene;

	scene = argument_handler(scene, argv, argc);
	if (scene.err_code < 0)
		return (ft_err(scene));
	cnx = mlx_init();
	win = mlx_new_window(cnx, scene.config.width,
						scene.config.height, "My miniRT");
	img.img = mlx_new_image(cnx, scene.config.width, scene.config.height);
	skybox.img = mlx_xpm_file_to_image(cnx, "./srcs/stars.xpm",
									&skybox.bpp, &skybox.bpp);
	skybox.addr = mlx_get_data_addr(skybox.img,
					&skybox.bpp, &skybox.line_length, &skybox.endian);
	mlx_put_image_to_window(cnx, win, skybox.img, 0, 0);
	img.addr = mlx_get_data_addr(img.img,
				&img.bpp, &img.line_length, &img.endian);
	mlx_key_hook(win, keys, &scene);
	mlx_hook(win, 17, 0, close_win, &scene);
	ft_render(scene, 0, vector3(0, 0, 0), vector3(0, 0, 0));
	if (scene.save == 0)
		mlx_loop(cnx);
	else
		save_bmp("hey.bmp", scene.config, (int *)mlx_get_data_addr(img.img,
						&img.bpp, &img.line_length, &img.endian));
	return (0);
}
