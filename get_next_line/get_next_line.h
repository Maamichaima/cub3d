/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:25:56 by cmaami            #+#    #+#             */
/*   Updated: 2023/12/06 19:05:46 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin_(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(char *s, int c);
char	*get_next_line(int fd);

#endif