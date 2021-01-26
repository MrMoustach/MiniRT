/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:02:43 by iharchi           #+#    #+#             */
/*   Updated: 2021/01/26 12:21:50 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
		if (line[i] != ' ')
			enter = 1;
		if (enter)
			ret[j++] = line[i];
		if (line[i] == ' ')
			enter = 0;
		i++;
	}
	ret[j] = '\0';
	free(line);
	return (ret);
}

int		get_type(char *type)
{
	if (type == NULL)
		return (-1);
	if (*type == '#')
		return (-1);
	if (!ft_strncmp(type, "R", 2))
		return (0);
	if (!ft_strncmp(type, "A", 2))
		return (1);
	if (!ft_strncmp(type, "c", 2))
		return (2);
	if (!ft_strncmp(type, "l", 2))
		return (3);
	if (!ft_strncmp(type, "sp", 2))
		return (4);
	if (!ft_strncmp(type, "pl", 2))
		return (5);
	if (!ft_strncmp(type, "sq", 2))
		return (6);
	if (!ft_strncmp(type, "cy", 2))
		return (7);
	if (!ft_strncmp(type, "tr", 2))
		return (8);
	if (!ft_strncmp(type, "sk", 2))
		return (9);
	if (!ft_strncmp(type, "as", 2))
		return (10);
	return (11);
}

void	init_scene(t_scene *scene)
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
	(*scene).skybox = 0;
	(*scene).ascii = 0;
}

int		check_rt_file(char *file, t_scene *scene)
{
	char *file_at_point;

	init_scene(scene);
	file_at_point = ft_strrchr(file, '.') + 1;
	if (file_at_point == (char *)1)
		return (-1);
	if (ft_strncmp(file_at_point, "rt", 3))
		return (-1);
	return (1);
}

t_scene	ft_parse(t_scene scene, char *file)
{
	char	*line;
	int		fd;
	int		n;

	scene.err_code = check_rt_file(file, &scene);
	if (scene.err_code >= 0 && (fd = open(file, O_RDONLY)) < 0)
		scene.err_code = -5;
	if (scene.err_code < 0)
		return (scene);
	while ((n = get_next_line(fd, &line)))
	{
		line = format_line(line);
		scene.line++;
		if (ft_line_parse(line, &scene) < 0)
			return (scene);
	}
	line = format_line(line);
	ft_line_parse(line, &scene);
	if (scene.cams == NULL)
		scene.err_code = -49;
	if (scene.am.set == 0)
		scene.err_code = -50;
	if (scene.config.set == 0)
		scene.err_code = -51;
	return (scene);
}
