/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 01:30:28 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/01 03:53:25 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int     ft_string_is_float(char *s)
{
    int n;
    int i;

    if (!s)
        return (0);
    n = ft_strlen(s);
    i = 0;
    while (i < n)
    {
        if (!ft_isdigit(s[i]))
        {
            if (s[i] == '.' || s[i] == '+' || s[i] == '-')
            {
                i++;
                continue ;
            }
            return (0);
        }
        i++;
    }
    return (1);
}

int ft_string_is_int(char *s)
{
    int n;
    int i;

    if (!s)
        return (0);
    n = ft_strlen(s);
    i = 0;
    while (i < n)
    {
        if (!ft_isdigit(s[i++]))
            return (0);
    }
    return (1);
}

t_rgb   ft_is_color_good(char **tab)
{
    int     r;
    int     g;
    int     b;

    if (!ft_string_is_int(tab[0]) || !ft_string_is_int(tab[1]) || !ft_string_is_int(tab[2]))
        return (rgb(-1,0,0));
    if (tab[3] != '\0')
        return (rgb(-1,0,0));
    r = ft_atoi(tab[0]);
    g = ft_atoi(tab[1]);
    b = ft_atoi(tab[2]);
    if (r < 0 || b < 0 || g < 0)
        return (rgb(-1, 0, 0));
    if (r > 255 || b > 255 || g > 255)
        return (rgb(-1, 0, 0));
    return(rgb(r, g, b));
}

t_vector3   ft_is_point_good(char **tab, int *err)
{
    *err = 0;
    if (!ft_string_is_float(tab[0]) || !ft_string_is_float(tab[1]) || !ft_string_is_float(tab[2]))
        return vector3(*err = -1, 0, 0);
    if (tab[3])
        return vector3(*err = -1, 0, 0);
    return(vector3(ft_parse_float(tab[0]), ft_parse_float(tab[1]), ft_parse_float(tab[2])));
}

t_vector3   ft_is_direction_good(char **tab, int *err)
{
    t_vector3   v;

    v = ft_is_point_good(tab, err);
    if (err < 0)
        return (v);
    if (v.x == 0 && v.y == 0 && v.z == 0)
        return vector3(*err = -1, 0, 0);
    return (v);
}