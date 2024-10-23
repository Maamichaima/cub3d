/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:44:38 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/23 19:07:41 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	check_vert_hitwall(t_data *data, int index, t_coordinate inter, t_coordinate step)
{
	double	next_inter_x;
	double	next_inter_y;
	double	is_wall_flag;
	double	x_wall;
	double	y_wall;
	double	vert_distance;
	int		is_door;
	int		is_open_door;

	is_wall_flag = 0;
	x_wall = 0;
	y_wall = 0;
	vert_distance = 0;
	is_door = 0;
	is_open_door = 0;
	int a, b;
	next_inter_x = inter.x;
	next_inter_y = inter.y;
	if (Ray_LEFT(data->ray[index]))
		next_inter_x -= 0.00001;
	while (next_inter_x >= 0 && next_inter_x < (data->width * SCALE)
		&& next_inter_y >= 0 && next_inter_y < (data->height * SCALE))
	{
		if (!is_open_door && hit_o(*data, next_inter_x, next_inter_y))
		{
			data->ray[index].x = next_inter_x;
			data->ray[index].y = next_inter_y;
			is_open_door = 1;
		}
		if (is_wall(*data, next_inter_x, next_inter_y))
		{
			x_wall = next_inter_x;
			y_wall = next_inter_y;
			is_wall_flag = 1;
			break ;
		}
		else if (hit_door(data, index, next_inter_x, next_inter_y))
		{
			x_wall = next_inter_x;
			y_wall = next_inter_y;
			is_door = 1;
			break ;
		}
		next_inter_x += step.x;
		next_inter_y += step.y;
	}
	vert_distance = Distance_2Points(data->player.x, data->player.y, x_wall,
			y_wall);
	if (vert_distance < data->ray[index].distance)
	{
		data->ray[index].distance = vert_distance;
		data->ray[index].wall_inter_x = x_wall;
		data->ray[index].wall_inter_y = y_wall;
		data->ray[index].direction = 'v';
		data->ray[index].is_door = is_door;
	}
}

void	first_V_inter(int index, t_data *data)
{
	t_coordinate inter;
	t_coordinate step;
	
	inter.x = 0;
	inter.y = 0;
	step.x = 0;
	step.y = 0;

	inter.x = (int)floor(data->player.x / SCALE) * SCALE;
	if (Ray_RIGHT(data->ray[index]))
		inter.x += (SCALE);
	inter.y = data->player.y + ((inter.x - data->player.x)
			* tan(data->ray[index].ray_angle));
	step.x = SCALE;
	if (Ray_LEFT(data->ray[index]))
		step.x *= -1;
	step.y = (SCALE * tan(data->ray[index].ray_angle));
	if (Ray_UP(data->ray[index]) && step.y > 0)
		step.y *= -1;
	if (Ray_DOWN(data->ray[index]) && step.y < 0)
		step.y *= -1;
	check_vert_hitwall(data, index, inter, step);
}
