/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:45:54 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 15:34:56 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x
			* (data->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	color_one_square(int start_x, int start_y, void *x, double scale)
{
	int		i;
	int		j;
	double	s_x;
	double	s_y;
	int		color;

	i = 0;
	j = 0;
	s_x = start_x - MINIMAP_SCALE / 2;
	s_y = start_y - MINIMAP_SCALE / 2;
	color = 0xf54242;
	while (i <= MINIMAP_SCALE)
	{
		j = 0;
		while (j <= MINIMAP_SCALE)
		{
			if (i <= (MINIMAP_SCALE - 3) && j <= (MINIMAP_SCALE - 3) && i >= 3
				&& j >= 3)
				my_mlx_pixel_put(x, (s_x + i), (s_y + j), color);
			j++;
		}
		i++;
	}
}

void	draw_line_angle(t_data *data, int x0, int y0)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < LIGNE_OF_PLAYER)
	{
		x = x0 + i * cos(data->player.angle);
		y = y0 + i * sin(data->player.angle);
		if (x >= 0 && y >= 0)
			my_mlx_pixel_put(data, x, y, 0xff0000);
		i++;
	}
}

void	clear_img(t_data *x)
{
	double	i;
	double	j;

	i = 0;
	j = 0;
	while (i < (HEIGHT))
	{
		j = 0;
		while (j < WIDTH)
		{
			my_mlx_pixel_put(x, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int	draw(t_data *data)
{
	clear_img(data);
	key_hook(data);
	cast_ray(data, data->player.x, data->player.y);
	render_projected_wall(data);
	animation(data);
	mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->image.ptr_img,
		0, 0);
	return (0);
}
