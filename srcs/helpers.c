/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 01:30:28 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/24 04:29:35 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int			ft_string_is_float(char *s)
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

int			ft_string_is_good_intensity(char *s)
{
	float in;

	if (!ft_string_is_float(s))
		return (0);
	in = ft_parse_float(s);
	if (in < 0.0 || in > 1.0)
		return (0);
	return (1);
}

int			ft_string_is_good_diameter(char *s)
{
	float d;

	if (!ft_string_is_float(s))
		return (0);
	d = ft_parse_float(s);
	if (d < 0.0)
		return (0);
	return (1);
}

int			ft_string_is_int(char *s)
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

t_vector3	ft_is_point_good(char **tab, int *err)
{
	*err = 0;
	if (!ft_string_is_float(tab[0]) || !ft_string_is_float(tab[1]) ||
		!ft_string_is_float(tab[2]))
		return (vector3(*err = -1, 0, 0));
	if (tab[3])
		return (vector3(*err = -1, 0, 0));
	return (vector3(ft_parse_float(tab[0]),
			ft_parse_float(tab[1]), ft_parse_float(tab[2])));
}
