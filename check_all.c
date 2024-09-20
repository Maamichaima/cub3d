/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:05:12 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/20 20:31:49 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int check_all(t_data *x)
{
	t_texture *t;
	int fd;
	int i = 0;

	
	fd = open(x->file_map, O_RDONLY);
	t = get_texture(fd);
	fd = open(x->file_map, O_RDONLY);
	get_map(fd ,x);
	char **c = fillBlanks(*x);
	if(check_zero_in_map(c, *x) && check_textures(t))
		printf("map valide\n");
	else
		printf("map not valide\n");
	return 0;
}