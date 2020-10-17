/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:05:02 by iharchi           #+#    #+#             */
/*   Updated: 2020/03/04 20:37:11 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int		ft_lookfor(char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (!(s[i++]))
			return (-1);
	}
	return (i);
}

int		ft_size(int nbr)
{
	int	i;

	i = 0;
	while (nbr / 10)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

int		count_zeros(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '0')
		i++;
	return (i);
}
float	ft_parse_float(char *s)
{
	int		p;
	float	nbr;
	float	nbr2;
	int		signe;

	p = ft_lookfor(s, '.');
	nbr = ft_atoi(s);
	signe = 1;
	if (nbr < 0)
	{
		signe = -1;
		nbr *= -1;
	}
	if (p >= 0)
		nbr2 = ft_atoi(&s[p + 1]);
	nbr += nbr2 / powf(10, ft_size(nbr2) + 1 + count_zeros(&s[p + 1]));
	return (nbr * signe);
}