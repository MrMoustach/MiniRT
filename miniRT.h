/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:53:42 by iharchi           #+#    #+#             */
/*   Updated: 2020/10/27 23:32:09 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <mlx.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "types.h"
# include "keys.h"
# include <time.h>
#include "debug.h"

int 	map_to_sphere(t_sphere *s, t_vector3 center, float radius,t_vector3 color);
int 	map_to_vector3(t_vector3 *v, float x, float y, float z);
int 	create_ray(t_ray *ray,t_vector3 p1, t_vector3 p2);
float	ft_dot(t_vector3 v1, t_vector3 v2);
t_vector3	ft_minus(t_vector3 v1, t_vector3 v2);
t_vector3	ft_plus(t_vector3 v1, t_vector3 v2);
t_hit	ft_sp_intersect(t_ray ray, t_sphere sphere);
int		ft_ambient(t_ambient *am,float bright,float x, float y, float z);
t_vector3	ft_get_point(t_ray ray, float sol);
int		ft_light(t_light *l, t_vector3 pos, float r, float g, float b, float bright);
t_vector3	ft_normalize(t_vector3	v);
int		ft_reverse(t_vector3 *v);
float	ft_mag(t_vector3 v);
unsigned	int		ft_rgbtohex(t_rgb color);
int		ft_multiply(t_vector3 *v, float n);
float	ft_abs(float a);
void 	put_pix(double x, double y, int color);
t_sphere	sphere(t_vector3 center, float radius, t_rgb color);
t_vector3	vector3(float x, float y, float z);
t_light		light(t_vector3 pos, t_rgb color, float bright);
t_ray		ray(t_vector3 p1, t_vector3 p2);
t_ambient	ambient(float bright, t_rgb color);
t_vector3	ft_multi(t_vector3 v, float d);
float	clamp(float min, float val, float max);
t_rgb		add_color(t_rgb c1, t_rgb c2);
t_rgb		clamp_color(t_rgb v);
t_rgb	rgb_multi(t_rgb rgb, float f);
t_vector3 sphere_normal(t_vector3 c, t_vector3 pi);
t_rgb	rgb(int x, int y, int z);
int			plane_intersect(t_ray r, t_plane p, float *t);
t_plane	plane(t_vector3 p, t_vector3 n, t_rgb c);
float	ft_parse_float(char *s);
t_scene	ft_parse(char *file);
t_cam		cam(t_ray ray, int fov);
void    ft_render(t_scene scene, int flag, t_vector3 mov, t_vector3 rot);
t_rgb	ft_calc_light(t_scene scene, t_hit hit);
t_vector3	ft_cross(t_vector3 v1, t_vector3 v2);
t_hit	ft_intersections(t_scene scene,t_ray r);
t_hit	ft_pl_intersect(t_ray ray, t_plane pl);
t_square	square(t_vector3 p, t_vector3 n, float size, t_rgb c);
t_hit	ft_sq_intersect(t_ray ray, t_square sq, t_scene scene);
t_cylinder	cylinder(t_vector3 p, t_vector3 n, float d, float h, t_rgb c);
t_hit ft_cy_intersect(t_ray ray, t_cylinder cy);
t_triangle	triangle(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_rgb co);
t_hit	ft_tr_intersect(t_ray ray, t_triangle tr);
t_cam   ft_get_cam(t_scene scene, int flag, t_vector3 mov, t_vector3 rot);
int		ft_same_vector(t_vector3 v1, t_vector3 v2);
int	get_type(char *type);
int		checkSum_line(char *line);
void	free_tab(char **tab);
t_vector3	rotate_vector(t_vector3 v, t_vector3 rot);

int		save_bmp(const char *filename, t_config config, int *image);


void        *cnx;
void        *win;
t_img       img;
#endif
