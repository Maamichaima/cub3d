/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:05:12 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/10 15:50:41 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int check_all(t_data *x)
{
	int fd;

	fd = open(x->file_map, O_RDONLY);
	x->texture = get_texture(fd);
	// fd = open(x->file_map, O_RDONLY);
	// get_map(fd ,x);
	// printf("%s   %s \n", t->attr, t->data);
	char **c = fillBlanks(*x);
	if(checkPlayer(x->map) && check_zero_in_map(c, *x) && check_textures(x->texture))
	{
		printf("map valide\n");
		return 1;
	}
	else
	{
		printf("map not valide\n");
		return 0;
	}
}
