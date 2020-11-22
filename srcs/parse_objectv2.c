/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objectv2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:48:37 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/22 04:29:29 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	parse_config(char **tab, t_scene *scene)
{
	int	width;
	int height;

	if (!tab[1] || !tab[2])
		scene->err_code = -7;
	if (tab[3] != '\0')
		scene->err_code = -10;
	if (scene->config.set == 1)
		scene->err_code = -6;
	if (scene->err_code < 0)
		return ;
	width = ft_atoi(tab[1]);
	height = ft_atoi(tab[2]);
	if (width <= 0)
		scene->err_code = -8;
	if (height <= 0)
		scene->err_code = -9;
	if (scene->err_code < 0)
		return ;
	(*scene).config.width = width;
	(*scene).config.height = height;
	(*scene).config = ft_check_res((*scene).config);
	(*scene).config.set = 1;
}

int		ft_line_parse(char *line, t_scene *scene)
{
	char	**tab;
	int		type;

	if (*line == '\0')
		return (scene->err_code = -2);
	tab = ft_split(line, ' ');
	type = get_type(tab[0]);
	if (type == -1)
		return (1);
	if (type == 0)
		parse_config(tab, scene);
	if (type > 3)
		(*scene).obj_count++;
	if (type == 1)
		(*scene).am = parse_ambient(tab, scene);
	else if (type == 2)
		parse_cam(tab, scene);
	else if (type == 3)
		parse_light(tab, scene);
	else if (type == 4)
		parse_sphere(tab, scene);
	else if (type == 5)
		parse_plane(tab, scene);
	else if (type == 6)
		parse_square(tab, scene);
	else if (type == 7)
		parse_cylinder(tab, scene);
	else if (type == 8)
		parse_triangle(tab, scene);
	else if (type == 9)
		scene->skybox = 1;
	else if (type == 10)
		scene->err_code = -48;
	free_tab(tab);
	free(line);
	return (scene->err_code);
}

void	parse_square(char **tab, t_scene *scene)
{
	t_object	*ob;
	char		**t;

	if (!tab[1] || !tab[2] || !tab[3] || !tab[4] || tab[5])
		return ((void)(scene->err_code = -32));
	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1], ',');
	(*ob).square.p = ft_is_point_good(t, &((*ob).square.color.g));
	if (((*ob).square.color.g) < 0)
		scene->err_code = -33;
	free_tab(t);
	t = ft_split(tab[2], ',');
	(*ob).square.n = ft_is_direction_good(t, &((*ob).square.color.g));
	if (((*ob).square.color.g) < 0)
		scene->err_code = -34;
	free_tab(t);
	if (!ft_string_is_good_diameter(tab[3]))
		scene->err_code = -35;
	t = ft_split(tab[4], ',');
	(*ob).square.color = ft_is_color_good(t);
	if (((*ob).square.color).r < 0)
		scene->err_code = -36;
	(*ob).square.size = ft_parse_float(tab[3]);
	(*ob).square.id = scene->obj_count - 1;
	(*ob).type = 6;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void	parse_cylinder(char **tab, t_scene *scene)
{
	t_vector3	v;
	t_vector3	v2;
	t_rgb		r;
	t_object	*ob;
	char		**t;
	int			err;

	if (!tab[1] || !tab[2] || !tab[3] || !tab[4] || !tab[5] || tab[6])
		return ((void)(scene->err_code = -32));
	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1], ',');
	v = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -38;
	free_tab(t);
	t = ft_split(tab[2], ',');
	v2 = ft_is_direction_good(t, &err);
	if (err < 0)
		scene->err_code = -39;
	free_tab(t);
	if (!ft_string_is_good_diameter(tab[3]))
		scene->err_code = -40;
	if (!ft_string_is_good_diameter(tab[4]))
		scene->err_code = -41;
	t = ft_split(tab[5], ',');
	r = ft_is_color_good(t);
	if (r.r < 0)
		scene->err_code = -32;
	(*ob).cylinder = cylinder(v, v2, ft_parse_float(tab[3]), ft_parse_float(tab[4]), r);
	(*ob).cylinder.id = scene->obj_count - 1;
	(*ob).type = 7;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void	parse_triangle(char **tab, t_scene *scene)
{
	t_vector3	v;
	t_vector3	v2;
	t_vector3	v3;
	t_rgb		r;
	t_object	*ob;
	char		**t;
	int			err;

	if (!tab[1] || !tab[2] || !tab[3] || !tab[4] || tab[5])
		return ((void)(scene->err_code = -43));
	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1], ',');
	v = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -44;
	free_tab(t);
	t = ft_split(tab[2], ',');
	v2 = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -45;
	free_tab(t);
	t = ft_split(tab[3], ',');
	v3 = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -46;
	free_tab(t);
	t = ft_split(tab[4], ',');
	r = ft_is_color_good(t);
	if (r.r < 0)
		scene->err_code = -47;
	(*ob).triangle = triangle(v, v2, v3, r);
	(*ob).triangle.id = scene->obj_count - 1;
	(*ob).type = 8;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}
