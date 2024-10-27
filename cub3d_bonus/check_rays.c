/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:50:58 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 13:58:57 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ray_up(t_ray ray)
{
	if (ray.ray_angle >= PI && ray.ray_angle < 2 * PI)
		return (1);
	return (0);
}

int	ray_down(t_ray ray)
{
	if (ray.ray_angle >= 0 && ray.ray_angle < PI)
		return (1);
	return (0);
}

int	ray_right(t_ray ray)
{
	if (ray.ray_angle <= (PI / 2) || ray.ray_angle > (3 * PI / 2))
		return (1);
	return (0);
}

int	ray_left(t_ray ray)
{
	if (ray.ray_angle > (PI / 2) && ray.ray_angle <= (3 * PI / 2))
		return (1);
	return (0);
}

int	draw_ray(t_data *data, int x0, int y0, t_ray ray) //,int x_wall, int y_wall)
{
	int	i;
	int	d;
	int	x;
	int	y;

	i = 0;
	d = distance_2points(x0, y0, ray.wall_inter_x, ray.wall_inter_y);
	while (i < d)
	{
		x = x0 + i * cos(ray.ray_angle);
		y = y0 + i * sin(ray.ray_angle);
		if (x >= 0 && y >= 0)
			my_mlx_pixel_put(data, x * MINIMAP_SCALE, y * MINIMAP_SCALE,
				0xFFFF33);
		i++;
	}
	return (0);
}
