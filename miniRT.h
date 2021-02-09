/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 04:28:33 by iharchi           #+#    #+#             */
/*   Updated: 2021/01/26 11:02:49 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <mlx.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "types.h"
# include "keys.h"

int				map_to_sphere(t_sphere *s, t_vector3 center, float radius,
t_vector3 color);
int				map_to_vector3(t_vector3 *v, float x, float y, float z);
int				create_ray(t_ray *ray, t_vector3 p1, t_vector3 p2);
float			ft_dot(t_vector3 v1, t_vector3 v2);
t_vector3		ft_minus(t_vector3 v1, t_vector3 v2);
t_vector3		ft_plus(t_vector3 v1, t_vector3 v2);
t_hit			ft_sp_intersect(t_ray ray, t_sphere sphere);
int				ft_ambient(t_ambient *am, float bright, float x, float y,
float z);
t_vector3		ft_get_point(t_ray ray, float sol);
int				ft_light(t_light *l, t_vector3 pos, float r, float g, float b,
float bright);
t_vector3		ft_normalize(t_vector3 v);
t_vector3		ft_reverse(t_vector3 v);
float			ft_mag(t_vector3 v);
unsigned int	ft_rgbtohex(t_rgb color);
float			ft_fabs(float a);
void			put_pix(double x, double y, int color, int sk);
t_sphere		sphere(t_vector3 center, float radius, t_rgb color);
t_vector3		vector3(float x, float y, float z);
t_light			light(t_vector3 pos, t_rgb color, float bright);
t_ray			ray(t_vector3 p1, t_vector3 p2);
t_ambient		ambient(float bright, t_rgb color);
t_vector3		ft_multi(t_vector3 v, float d);
float			clamp(float min, float val, float max);
t_rgb			add_color(t_rgb c1, t_rgb c2);
t_rgb			clamp_color(t_rgb v);
t_rgb			rgb_multi(t_rgb rgb, float f);
t_rgb			rgb(int x, int y, int z);
t_plane			plane(t_vector3 p, t_vector3 n, t_rgb c);
float			ft_parse_float(char *s);
t_scene			ft_parse(t_scene s, char *file);
t_cam			cam(t_ray ray, int fov);
void			ft_render(t_scene scene, int flag, int key);
t_rgb			ft_calc_light(t_scene scene, t_hit hit);
t_vector3		ft_cross(t_vector3 v1, t_vector3 v2);
t_hit			ft_intersections(t_scene scene, t_ray r, float max);
t_hit			ft_pl_intersect(t_ray ray, t_plane pl);
t_square		square(t_vector3 p, t_vector3 n, float size, t_rgb c);
t_hit			ft_sq_intersect(t_ray ray, t_square sq);
t_cylinder		cylinder(t_vector3 p, t_vector3 n, t_vector3 v, t_rgb c);
t_hit			ft_cy_intersect(t_ray ray, t_cylinder cy);
t_triangle		triangle(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_rgb co);
t_hit			ft_tr_intersect(t_ray ray, t_triangle tr);
t_cam			ft_get_cam(t_scene scene, int flag, int key);
int				get_type(char *type);
void			free_tab(char **tab);
t_vector3		rotate_vector(t_vector3 v, t_vector3 rot);
int				save_bmp(const char *filename, t_config config, int *image);
int				ft_string_is_float(char *s);
int				ft_string_is_int(char *s);
t_rgb			ft_is_color_good(char **tab);
t_vector3		ft_is_point_good(char **tab, int *err);
t_vector3		ft_is_direction_good(char **tab, int *err);
int				ft_string_is_good_intensity(char *s);
int				ft_string_is_good_diameter(char *s);
int				ft_err(t_scene scene);
int				close_win(int key, void *param);
void			ft_keys_to_cam(int key, t_scene *sc);
void			ft_re_render(t_scene scene, int flag, int key);
int				ft_line_parse(char *line, t_scene *scene);
void			parse_config(char **tab, t_scene *scene);
void			parse_triangle(char **tab, t_scene *scene);
void			parse_cylinder(char **tab, t_scene *scene);
void			parse_square(char **tab, t_scene *scene);
void			parse_plane(char **tab, t_scene *scene);
void			parse_cam(char **tab, t_scene *scene);
void			parse_light(char **tab, t_scene *scene);
void			parse_sphere(char **tab, t_scene *scene);
t_ambient		parse_ambient(char **tab, t_scene *scene);
t_config		ft_check_res(t_config config);
void			ft_line_parse_helper(int type, char **tab, t_scene *scene);
void			parse_square_helper(t_scene *scene, t_square sq);
void			parse_cylinder_helper(t_scene *scene, t_cylinder cy, int err);
void			parse_triangle_helepr(t_scene *s, t_vector3 v, t_vector3 v2,
char **ta);
t_ray			make_ray(t_scene scene, t_cam camera, float u, float v);
void			bit_shift(unsigned char *arr, int val);
t_vector3		get_rotation(t_vector3 v, t_vector3 ref);
t_vector3		move_cam(t_cam cam, int key);
t_vector3		rotate_cam(t_cam cam, int key);
t_tuple		    get_spherical_cords(t_vector3 p, t_sphere sp);
t_rgb		    get_uv_pattern(t_tuple uv, int h, int w);
t_tuple		    get_planar_cords(t_vector3 p, t_plane plane);
t_tuple		    get_cylindrical_cords(t_vector3 p, t_cylinder cy);
t_rgb		get_uv_map(t_tuple uv);
void			*g_cnx;
void			*g_win;
t_img			g_img;
t_img			g_skybox;
t_img           g_uvmap;
#endif
