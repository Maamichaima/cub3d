/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:34:56 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 14:48:12 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	draw_rect(t_data *data, double wall_height, int j, int color)
{
	int	lim;
	int	i;

	lim = (HEIGHT / 2) + wall_height / 2;
	i = (HEIGHT / 2) - wall_height / 2;
	if (lim > HEIGHT)
		lim = HEIGHT;
	while (i < lim)
	{
		if (i >= 0 && i < HEIGHT)
			my_mlx_pixel_put(data, j, i, color);
		i++;
	}
}

int	set_wall_color(t_ray ray)
{
	if (ray.direction == 'h')
	{
		if (ray.ray_angle > 0 && ray.ray_angle < PI)
			return (0xD239FF);
		else
			return (0xFF25CD);
	}
	else if (ray.direction == 'v')
	{
		if (ray.ray_angle < (PI / 2) || ray.ray_angle > 3 * (PI / 2))
			return (0x66D7FF);
		else
			return (0xFFF666);
	}
	return (0);
}

double	get_start_text(t_ray ray, t_texture tex)
{
	double	d;

	if (ray.direction == 'h')
	{
		d = (long long)ray.wall_inter_x / SCALE * SCALE;
		d = (ray.wall_inter_x - d) / SCALE * tex.width;
	}
	else
	{
		d = (long long)ray.wall_inter_y / SCALE * SCALE;
		d = (ray.wall_inter_y - d) / SCALE * tex.width;
	}
	return (d);
}

t_texture	get_wall_tex(t_ray ray, t_data data)
{
	t_texture	*t;

	t = data.texture;
	if (ray.direction == 'h')
	{
		if (ray.ray_angle > 0 && ray.ray_angle < PI)
			return (hh(data.texture, "SO"));
		else
			return (hh(data.texture, "NO"));
	}
	else
	{
		if (ray.ray_angle < (PI / 2) || ray.ray_angle > 3 * (PI / 2))
			return (hh(data.texture, "EA"));
		else
			return (hh(data.texture, "WE"));
	}
}

unsigned int	darkness(unsigned int color, double distance, int max_distance)
{
	double	dark_factor;
	int		r;
	int		g;
	int		b;

	dark_factor = 1 - (distance / max_distance);
	if (dark_factor < 0)
		dark_factor = 0;
	if (dark_factor > 1)
		dark_factor = 1;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = r * dark_factor;
	g = g * dark_factor;
	b = b * dark_factor;
	return ((r << 16) | (g << 8) | b);
}
