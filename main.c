/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:50:13 by iharchi           #+#    #+#             */
/*   Updated: 2020/10/25 03:05:08 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
void	ft_re_render(t_scene scene, int flag, t_vector3 mov, t_vector3 rot)
{
	mlx_destroy_image(cnx, img.img);
	img.img = mlx_new_image(cnx, scene.config.width, scene.config.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	ft_render(scene, flag, mov, rot);
	//mlx_put_image_to_window(cnx,win,img.img,0,0);
}
int keys(int key, void *param)
{
	t_scene	scene;

	scene = *((t_scene *) param);
	if (key == KEY_ESC)
		exit(0);
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
	printf("%d\n",key);
	return (0);    
}

int main(int argc, char *argv[])
{
	t_scene scene;

	if (argc > 3 || argc < 2)
	{
		ft_putstr_fd("Error\n",1);
		return (0);
	}
	scene = ft_parse(argv[1]);
	if (scene.err_code < 0)
	{
		printf("there was an error with the code {%d} //hey implement error msgs dumbass", scene.err_code);
		return (-1);
	}
	cnx = mlx_init();
	win = mlx_new_window(cnx, scene.config.width, scene.config.height, "My miniRT");
	img.img = mlx_new_image(cnx,scene.config.width, scene.config.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	mlx_key_hook(win,keys,&scene);
	ft_render(scene, 0, vector3(0, 0, 0), vector3(0, 0, 0));
	//mlx_put_image_to_window(cnx,win,img.img,0,0);
	
	mlx_loop(cnx);
} 