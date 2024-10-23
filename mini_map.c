/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:53:33 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/22 21:32:43 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	cast_ray_mini_map(t_data *x)
{
	int	i;

	i = 0;
	while (i < x->num_rays)
	{
		draw_ray(x, x->player.x, x->player.y, x->ray[i]);
		i++;
	}
}

void	mini_map(t_data *x)
{
	double	width;
	double	height;
	double	start_x;
	double	start_y;

	width = 20;
	height = 20;
	start_x = x->player.x - SCALE * width / 2;
	start_y = x->player.y - SCALE * height / 2;
	double i, j;
	double b, a;
	i = MINIMAP_SCALE;
	while (i < height * MINIMAP_SCALE)
	{
		j = MINIMAP_SCALE;
		while (j < width * MINIMAP_SCALE)
		{
			a = start_y / SCALE + i / MINIMAP_SCALE;
			b = start_x / SCALE + j / MINIMAP_SCALE;
			if (a >= 0 && a < x->height && b >= 0 && b < x->width
				&& ((int)(start_x * MINIMAP_SCALE / SCALE + j)
					% MINIMAP_SCALE == 0 || (int)(start_y * MINIMAP_SCALE
						/ SCALE + i) % MINIMAP_SCALE == 0))
				my_mlx_pixel_put(x, j, i, 0x000000);
			else if (a >= 0 && a < x->height && b >= 0 && b < x->width
				&& x->map[(int)a][(int)b] == '1')
				my_mlx_pixel_put(x, j, i, 0xe0d5d9);
			else if (a >= 0 && a < x->height && b >= 0 && b < x->width
				&& x->map[(int)a][(int)b] == '0')
				my_mlx_pixel_put(x, j, i, 0x215dbf);
			j++;
		}
		i++;
	}
	color_one_square((width * MINIMAP_SCALE) / 2, (height * MINIMAP_SCALE) / 2,
		x, SCALE);
	draw_line_angle(x, (width * MINIMAP_SCALE) / 2, (height * MINIMAP_SCALE)
		/ 2);
}
