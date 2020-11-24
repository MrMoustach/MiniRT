/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:34:43 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:30:07 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ambient	parse_ambient(char **tab, t_scene *scene)
{
	char		**color;
	t_ambient	am;
	float		intensity;
	t_rgb		c;

	if (scene->am.set == 1)
		scene->err_code = -11;
	if (!tab[1] || !tab[2])
		scene->err_code = -12;
	if (tab[3] != '\0')
		scene->err_code = -13;
	if (scene->err_code < 0)
		return (am);
	if (!ft_string_is_good_intensity(tab[1]))
		scene->err_code = -14;
	intensity = ft_parse_float(tab[1]);
	color = ft_split(tab[2], ',');
	if (!color[0] || !color[1] || !color[2])
		scene->err_code = -15;
	c = ft_is_color_good(color);
	if (c.r < 0)
		scene->err_code = -15;
	am = ambient(intensity, c);
	am.set = 1;
	return (am);
}

void		parse_sphere(char **tab, t_scene *scene)
{
	t_vector3	v;
	t_rgb		color;
	char		**t;
	t_object	*ob;
	int			err;

	if (!tab[1] || !tab[2] || !tab[3] || tab[4])
		return ((void)(scene->err_code = -24));
	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1], ',');
	v = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -25;
	free_tab(t);
	t = ft_split(tab[3], ',');
	color = ft_is_color_good(t);
	if (color.r < 0)
		scene->err_code = -26;
	if (!ft_string_is_good_diameter(tab[2]))
		scene->err_code = -27;
	(*ob).sp = sphere(v, ft_parse_float(tab[2]), color);
	(*ob).type = 4;
	(*ob).sp.id = scene->obj_count - 1;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void		parse_light(char **tab, t_scene *scene)
{
	t_vector3	v;
	t_rgb		color;
	char		**t;
	t_light		*l;
	int			err;

	if (!tab[1] || !tab[2] || !tab[3] || tab[4])
		return ((void)(scene->err_code = -20));
	l = (t_light *)malloc(sizeof(t_light));
	t = ft_split(tab[1], ',');
	v = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -21;
	free_tab(t);
	t = ft_split(tab[3], ',');
	color = ft_is_color_good(t);
	if (color.r < 0)
		scene->err_code = -22;
	if (!ft_string_is_good_intensity(tab[2]))
		scene->err_code = -23;
	*l = light(v, color, ft_parse_float(tab[2]));
	(*scene).light_count++;
	ft_lstadd_back(&(*scene).lights, ft_lstnew(l));
}

void		parse_cam(char **tab, t_scene *scene)
{
	t_ray	ray;
	t_cam	*c;
	char	**t;
	int		err;

	if (!tab[1] || !tab[2] || !tab[3] || tab[4])
		return ((void)(scene->err_code = -16));
	c = (t_cam *)malloc(sizeof(t_cam));
	t = ft_split(tab[1], ',');
	ray.p1 = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -17;
	free_tab(t);
	t = ft_split(tab[2], ',');
	ray.p2 = ft_is_direction_good(t, &err);
	if (err < 0)
		scene->err_code = -18;
	free_tab(t);
	if (!ft_string_is_int(tab[3]))
		scene->err_code = -19;
	(*c) = cam(ray, ft_atoi(tab[3]));
	(*c).id = (*scene).cam_count;
	(*scene).cam_count++;
	ft_lstadd_back(&(*scene).cams, ft_lstnew(c));
}

void		parse_plane(char **tab, t_scene *scene)
{
	t_object	*ob;
	char		**t;
	int			err;

	if (!tab[1] || !tab[2] || !tab[3] || tab[4])
		return ((void)(scene->err_code = -28));
	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1], ',');
	(*ob).plane.p = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -29;
	free_tab(t);
	t = ft_split(tab[2], ',');
	(*ob).plane.n = ft_is_direction_good(t, &err);
	if (err < 0)
		scene->err_code = -30;
	free_tab(t);
	t = ft_split(tab[3], ',');
	(*ob).plane.color = ft_is_color_good(t);
	if ((*ob).plane.color.r < 0)
		scene->err_code = -31;
	(*ob).plane.id = scene->obj_count - 1;
	(*ob).type = 5;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}
