/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:32:31 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 15:34:46 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double	dmod(double x, double y)
{
	return (x - (long long)(x / y) *y);
}

void	protect_dark_factor(double *dark_factor)
{
	if (*dark_factor < 0)
		*dark_factor = 0;
	if (*dark_factor > 1)
		*dark_factor = 1;
}

double	distance_from_center(double j)
{
	double	distance_from_center;

	if (j < HEIGHT / 2)
		distance_from_center = HEIGHT / 2 - j;
	else
		distance_from_center = j - HEIGHT / 2;
	return (distance_from_center);
}

t_texture	hh(t_texture *t, char *str)
{
	while (t)
	{
		if (ft_strcmp(t->attr, str) == 0)
			return (*t);
		t = t->next;
	}
	return (*t);
}

unsigned int my_mlx_pixel_get(t_image image, int x, int y)
{
	char	*dst;

	dst = image.addr + (y * image.line_length + x * (image.bits_per_pixel / 8));
	return *((unsigned int*)dst);
}
