/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:05:12 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/23 00:07:52 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int check_all(t_data *x)
{
	int fd;
	char **c;

	fd = open(x->file_map, O_RDONLY);
	x->texture = get_texture(fd);
	c = fillBlanks(*x);
	if(checkPlayer(x->map) && check_zero_in_map(c, *x) && check_textures(x->texture,x))
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
