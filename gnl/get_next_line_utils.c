/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:50:03 by iharchi           #+#    #+#             */
/*   Updated: 2020/01/04 01:17:27 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_iselig(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i++] == '\n')
			return (0);
	}
	return (1);
}

char	*ft_strncpy(char *dest, char const *src, unsigned int n, char stop)
{
	int		i;

	i = 0;
	while (src[i] && n > 0 && src[i] != stop)
	{
		dest[i] = src[i];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, char const *src, int nb)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && nb > 0 && src[j] != '\n')
	{
		dest[i + j] = src[j];
		j++;
		nb--;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*resetbuff(char *buff)
{
	int	i;

	i = 0;
	if (!buff)
		return (buff);
	while (buff[i] != '\0')
		buff[i++] = '\0';
	return (buff);
}
