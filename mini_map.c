/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:53:33 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 14:11:21 by maamichaima      ###   ########.fr       */
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

int	is_corner(char c)
{
	if (!c || c == ' ' || c == '\n')
		return (0);
	return (1);
}

void	put_pixel_mini_map(t_data *x, double i, double j, t_coordinate start)
{
	double	b;
	double	a;

	a = start.y / SCALE + i / MINIMAP_SCALE;
	b = start.x / SCALE + j / MINIMAP_SCALE;
	if (a >= 0 && a < x->height && b >= 0 && b < x->width && is_corner(x->map[(int)a][(int)b]) && ((int)(start.x * MINIMAP_SCALE / SCALE + j) % MINIMAP_SCALE == 0
		|| (int)(start.y * MINIMAP_SCALE / SCALE + i) % MINIMAP_SCALE == 0))
		my_mlx_pixel_put(x, j, i, 0x000000);
	else if (a >= 0 && a < x->height && b >= 0 && b < x->width
		&& x->map[(int)a][(int)b] == '1')
		my_mlx_pixel_put(x, j, i, 0xe0d5d9);
	else if (a >= 0 && a < x->height && b >= 0 && b < x->width
		&& x->map[(int)a][(int)b] == '0')
		my_mlx_pixel_put(x, j, i, 0x215dbf);
}

void	mini_map(t_data *x)
{
	double			width;
	double			height;
	t_coordinate	start;
	double			i;
	double			j;

	width = 20;
	height = 20;
	start.x = x->player.x - SCALE * width / 2;
	start.y = x->player.y - SCALE * height / 2;
	i = MINIMAP_SCALE;
	while (i < height * MINIMAP_SCALE)
	{
		j = MINIMAP_SCALE;
		while (j < width * MINIMAP_SCALE)
		{
			put_pixel_mini_map(x, i, j, start);
			j++;
		}
		i++;
	}
	color_one_square((width * MINIMAP_SCALE) / 2, (height * MINIMAP_SCALE) / 2,
		x);
	draw_line_angle(x, (width * MINIMAP_SCALE) / 2, (height * MINIMAP_SCALE)
		/ 2);
}
