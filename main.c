/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:50:13 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/25 02:12:00 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_re_render(t_scene scene, int flag, t_vector3 mov, t_vector3 rot)
{
	mlx_destroy_image(g_cnx, g_img.img);
	g_img.img = mlx_new_image(g_cnx, scene.config.width, scene.config.height);
	g_img.addr = mlx_get_data_addr(g_img.img,
				&g_img.bpp, &g_img.line_length, &g_img.endian);
	ft_render(scene, flag, mov, rot);
}

int		keys(int key, void *param)
{
	t_scene scene;

	scene = *((t_scene *)param);
	if (key == KEY_ESC)
		close_win(0, param);
	ft_keys_to_cam(key, &scene);
	return (0);
}

int		close_win(int key, void *param)
{
	t_scene scene;

	scene = *((t_scene *)param);
	if (scene.line != 0 && key > 0)
		ft_lstclear(&(scene.objects), free);
	(void)key;
	exit(EXIT_SUCCESS);
	return (1);
}

t_scene	argument_handler(t_scene scene, char **argv, int argc)
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

int		main(int argc, char *argv[])
{
	t_scene scene;

	scene.err_code = 0;
	scene = argument_handler(scene, argv, argc);
	if (scene.err_code < 0)
		return (ft_err(scene));
	g_cnx = mlx_init();
	g_win = mlx_new_window(g_cnx, scene.config.width,
						scene.config.height, TITLE);
	g_img.img = mlx_new_image(g_cnx, scene.config.width, scene.config.height);
	g_skybox.img = mlx_xpm_file_to_image(g_cnx, SK_PATH,
									&g_skybox.bpp, &g_skybox.bpp);
	g_skybox.addr = mlx_get_data_addr(g_skybox.img,
					&g_skybox.bpp, &g_skybox.line_length, &g_skybox.endian);
	mlx_put_image_to_window(g_cnx, g_win, g_skybox.img, 0, 0);
	g_img.addr = mlx_get_data_addr(g_img.img,
								&g_img.bpp, &g_img.line_length, &g_img.endian);
	ft_render(scene, 0, vector3(0, 0, 0), vector3(0, 0, 0));
	mlx_key_hook(g_win, keys, &scene);
	mlx_hook(g_win, 17, 0, close_win, &scene);
	if (scene.save == 0)
		mlx_loop(g_cnx);
	else
		save_bmp(SAVE_PATH, scene.config, (int *)g_img.addr);
	return (0);
}
