/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:02:43 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/01 01:56:27 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

// TODO: read from .RT file 
int		checkSum_line(char *line)
{
	int type;
	char **tab;

	tab = ft_split(line, ' ');
	type = get_type(tab[0]);
	free_tab(tab);
	if(type < -1 || type > 8)
		return(-1);
	//printf("%d %s\n",type,line);
	return (0);
}

char	*format_line(char *line)
{
	char	enter;
	int		i;
	char	*ret;
	int		j;

	i = 0;
	j = 0;
	enter = 1;
	if (!(ret = (char *)malloc(strlen((const char *)line) + 1)))
		return (NULL);
	while (line[i] != '\0')
	{
		if(line[i] != ' ')
			enter = 1;
		if(enter)
			ret[j++] = line[i];
		if(line[i] == ' ')
			enter = 0;
		i++;
	}
	ret[j] = '\0';
	free(line);
	return (ret);
}

int	get_type(char *type)
{
	if (*type == '#')
		return (-1);
	if (!ft_strncmp(type, "R",2))
		return (0);
	if (!ft_strncmp(type, "A",2))
		return (1);
	if (!ft_strncmp(type, "c",2))
		return (2);
	if (!ft_strncmp(type, "l",2))
		return (3);
	if (!ft_strncmp(type, "sp",2))
		return (4);
	if (!ft_strncmp(type, "pl",2))
		return (5);
	if (!ft_strncmp(type, "sq",2))
		return (6);
	if (!ft_strncmp(type, "cy",2))
		return (7);
	if (!ft_strncmp(type, "tr",2))
		return (8);
	return (9);
}
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

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
		return am; //TODO : Free shit here
	if (!ft_string_is_float(tab[1]))
		scene->err_code = -14;
	intensity = ft_parse_float(tab[1]);
	color = ft_split(tab[2], ',');
	if (!color[0] || !color[1] || !color[2])
		scene->err_code = -15;
	c = ft_is_color_good(color);
	if (c.r < 0)
		scene->err_code = -15;
	am = ambient(intensity , c);
	free_tab(color);
	am.set = 1;
	return(am);
}

void	parse_sphere(char **tab, t_scene *scene)
{
	t_vector3 v;
	t_rgb color;
	char **t;
	t_object *ob;

	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1],',');
	v = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[3],',');
	color = rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_tab(t);
	(*ob).sp = sphere(v, ft_parse_float(tab[2]), color);
	(*ob).type = 4;
	(*ob).sp.id = scene->obj_count - 1;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}
void	parse_light(char **tab, t_scene *scene)
{
	t_vector3	v;
	t_rgb		color;
	char		**t;
	t_light		*l;
	
	l = (t_light *)malloc(sizeof(t_light));
	t = ft_split(tab[1],',');
	v = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[3],',');
	color = rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_tab(t);
	*l = light(v, color, ft_parse_float(tab[2]));
	(*scene).light_count++;
	ft_lstadd_back(&(*scene).lights, ft_lstnew(l));
}

void	parse_cam(char **tab, t_scene *scene)
{
	t_ray	ray;
	t_cam	*c;
	char	**t;
	int		err;

	c = (t_cam *)malloc(sizeof(t_cam));
	if (!tab[1] || !tab[2] || !tab[3] || tab[4])
		scene->err_code = -16;
	if (scene->err_code < 0)
		return (free(c));
	t = ft_split(tab[1], ',');
	ray.p1 = ft_is_point_good(t, &err);
	if (err < 0)
		scene->err_code = -17;
	free_tab(t);
	t = ft_split(tab[2],',');
	ray.p2 = ft_is_direction_good(t, &err);
	if (err < 0)
		scene->err_code = -18;
	free_tab(t);
	if (!ft_string_is_int(tab[3]))
		scene->err_code = -19;
	(*c) = cam(ray,ft_atoi(tab[3]));
	(*c).id = (*scene).cam_count;
	(*scene).cam_count++;
	ft_lstadd_back(&(*scene).cams, ft_lstnew(c));
}

void	parse_plane(char **tab, t_scene *scene)
{
	t_vector3 	v;
	t_vector3	v2;
	t_rgb 		r;
	t_object	*ob;
	char		**t;

	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1],',');
	v = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[2],',');
	v2 = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[3],',');
	r = rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_tab(t);
	(*ob).plane = plane(v, v2, r);
	(*ob).plane.id = scene->obj_count - 1;
	(*ob).type = 5;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void	parse_square(char **tab, t_scene *scene)
{
	t_vector3 	v;
	t_vector3	v2;
	t_rgb 		r;
	t_object	*ob;
	float		size;
	char		**t;

	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1],',');
	v = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[2],',');
	v2 = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	size = ft_atoi(tab[3]);
	t = ft_split(tab[4],',');
	r = rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_tab(t);
	(*ob).square = square(v, v2, size,r);
	(*ob).square.id = scene->obj_count - 1;
	(*ob).type = 6;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void	parse_cylinder(char **tab, t_scene *scene)
{
	t_vector3 	v;
	t_vector3	v2;
	t_rgb 		r;
	t_object	*ob;
	float		d;
	float		h;
	char		**t;

	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1],',');
	v = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[2],',');
	v2 = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	d = ft_atoi(tab[3]);
	h = ft_atoi(tab[4]);
	t = ft_split(tab[5],',');
	r = rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_tab(t);
	(*ob).cylinder = cylinder(v, v2, d, h, r);
	(*ob).cylinder.id = scene->obj_count - 1;
	(*ob).type = 7;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

void	parse_triangle(char **tab, t_scene *scene)
{
	t_vector3 	v;
	t_vector3	v2;
	t_vector3	v3;
	t_rgb 		r;
	t_object	*ob;
	char		**t;

	ob = (t_object *)malloc(sizeof(t_object));
	t = ft_split(tab[1],',');
	v = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[2],',');
	v2 = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[3],',');
	v3 = vector3(ft_parse_float(t[0]), ft_parse_float(t[1]), ft_parse_float(t[2]));
	free_tab(t);
	t = ft_split(tab[4],',');
	r = rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	free_tab(t);
	(*ob).triangle = triangle(v, v2, v3, r);
	(*ob).triangle.id = scene->obj_count - 1;
	(*ob).type = 8;
	ft_lstadd_back(&((*scene).objects), ft_lstnew(ob));
}

t_config	ft_check_res(t_config config)
{
	if (config.width > 2560)
		config.width = 2560;
	if (config.height > 1440)
		config.height = 1440;
	return (config);
}
void		parse_config(char **tab, t_scene *scene)
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
int		ft_line_parse(char *line,t_scene *scene)
{
	char	**tab;
	int		type;
	
	if (*line == '\0')
	{
		scene->err_code = -2;
		return (0);
	}
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
	else if(type == 2)
		parse_cam(tab,scene);
	else if (type == 3)
		parse_light(tab, scene);
	else if(type == 4)
		parse_sphere(tab, scene);
	else if(type == 5)
		parse_plane(tab, scene);
	else if(type == 6)
		parse_square(tab, scene);
	else if (type == 7)
		parse_cylinder(tab, scene);
	else if (type == 8)
		parse_triangle(tab, scene);
	return (scene->err_code);
}

void init_scene(t_scene *scene)
{
	(*scene).cam_count = 0;
	(*scene).light_count = 0;
	(*scene).obj_count = 0;
	(*scene).err_code = 0;
	(*scene).cams = NULL;
	(*scene).lights = NULL;
	(*scene).objects = NULL;
	(*scene).config.width = 0;
	(*scene).config.height = 0;
	(*scene).config.set = 0;
	(*scene).line = 0;
	(*scene).am.set = 0;
}
int		check_rt_file(char *file)
{
	char *file_at_point;

	file_at_point = ft_strrchr(file, '.') + 1;
	if (file_at_point == (char *)1)
		return (-1);
	if (ft_strncmp(file_at_point, "rt", 3))
		return (-1);
	return (1);
}
t_scene	ft_parse(t_scene s, char *file)
{
	char	*line;
	t_scene	scene;
	int fd;
	int	n;
	
	scene = s;
	if ((scene.err_code = check_rt_file(file)) < 0)
		return (scene);
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		scene.err_code = -5;
		return (scene);
	}
	init_scene(&scene);
	while ((n = get_next_line(fd, &line)))
	{
		line = format_line(line);
		scene.line++;
		//TODO : fix this shit
		if (ft_line_parse(line, &scene) < 0)
			return (scene);
		free(line);
	}
	if (scene.err_code >= 0)
	{
		line = format_line(line);
		ft_line_parse(line, &scene);
	}
	free(line);
	return (scene);
}
