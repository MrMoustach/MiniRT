/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:42:49 by iharchi           #+#    #+#             */
/*   Updated: 2020/12/01 02:03:01 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# define TRUE 1
# define FALSE 0
# define SK_PATH "./srcs/stars.xpm"
# define SAVE_PATH "img.bmp"
# define TITLE "My miniRT"

typedef struct	s_config
{
	int			width;
	int			height;
	int			set;
}				t_config;

typedef struct	s_vector3
{
	float		x;
	float		y;
	float		z;
}				t_vector3;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;
typedef struct	s_ray
{
	t_vector3	p1;
	t_vector3	p2;
	void		*hit;
}				t_ray;
typedef struct	s_cam
{
	t_ray		ray;
	float		fov;
	t_vector3	up;
	t_vector3	right;
	int			id;
	float		h;
	float		w;
}				t_cam;
typedef struct	s_sphere
{
	t_vector3	center;
	float		radius;
	t_rgb		color;
	int			id;
}				t_sphere;
typedef struct	s_light
{
	t_vector3	pos;
	float		bright;
	t_rgb		color;
}				t_light;
typedef struct	s_ambient
{
	float		bright;
	t_rgb		color;
	int			set;
}				t_ambient;
typedef struct	s_plane
{
	t_vector3	p;
	t_vector3	n;
	t_rgb		color;
	int			id;
}				t_plane;
typedef struct	s_square
{
	t_vector3	p;
	t_vector3	n;
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	t_vector3	p4;
	t_rgb		color;
	float		size;
	int			id;
}				t_square;
typedef struct	s_cylinder
{
	t_vector3	c;
	t_vector3	n;
	t_rgb		color;
	float		r;
	float		h;
	int			id;
}				t_cylinder;
typedef struct	s_triangle
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	t_rgb		color;
	int			id;
}				t_triangle;

typedef struct	s_object
{
	int			type;
	t_sphere	sp;
	t_square	square;
	t_plane		plane;
	t_cylinder	cylinder;
	t_triangle	triangle;
}				t_object;
typedef struct	s_hit
{
	t_vector3	normal;
	t_ray		ray;
	int			hit;
	float		sol;
	t_rgb		color;
	t_vector3	p;
	int			id;
}				t_hit;

typedef	struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_scene
{
	t_config	config;
	t_list		*objects;
	t_list		*cams;
	t_list		*lights;
	int			cam_count;
	int			obj_count;
	int			light_count;
	t_ambient	am;
	int			err_code;
	int			line;
	int			save;
	int			skybox;
}				t_scene;

#endif
