/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:07:48 by iharchi           #+#    #+#             */
/*   Updated: 2020/01/10 10:56:09 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

int		get_next_line(int fd, char **line);
char	*ft_strncpy(char *dest, char const *src, unsigned int n, char stop);
char	*ft_strncat(char *dest, char const *src, int nb);
char	*resetbuff(char *buff);
int		ft_iselig(char *s);
#endif
