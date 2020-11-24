/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 01:00:33 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:30:03 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	ft_line_parse_helper(int type, char **tab, t_scene *scene)
{
	if (type == 4)
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
}

void	parse_square_helper(t_scene *scene, t_square sq)
{
	t_object *ob;

	ob = (t_object *)malloc(sizeof(t_object));
	(*ob).square = sq;
	(*ob).square.id = scene->obj_count - 1;
	(*ob).type = 6;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void	parse_cylinder_helper(t_scene *scene, t_cylinder cy, int err)
{
	t_object	*ob;

	if (err < 0)
		scene->err_code = -39;
	ob = (t_object *)malloc(sizeof(t_object));
	(*ob).cylinder = cy;
	(*ob).cylinder.id = scene->obj_count - 1;
	(*ob).type = 7;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void	parse_triangle_helepr(t_scene *s, t_vector3 v, t_vector3 v2, char **ta)
{
	t_object	*ob;
	t_vector3	v3;
	t_rgb		r;
	char		**t;

	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(ta[3], ',');
	v3 = ft_is_point_good(t, &(r.g));
	if (r.g < 0)
		s->err_code = -46;
	free_tab(t);
	t = ft_split(ta[4], ',');
	r = ft_is_color_good(t);
	if (r.r < 0)
		s->err_code = -47;
	(*ob).triangle = triangle(v, v2, v3, r);
	(*ob).triangle.id = s->obj_count - 1;
	(*ob).type = 8;
	ft_lstadd_back(&((*s).objects), ft_lstnew(ob));
}
