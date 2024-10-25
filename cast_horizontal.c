/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:38:33 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 14:06:26 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_last_inter_horz(t_data *data, int index, t_coordinate next_inter,
		t_coordinate *wall)
{
	if (!data->ray[index].is_open && hit_o(*data, next_inter.x, next_inter.y))
	{
		data->ray[index].x = next_inter.x;
		data->ray[index].y = next_inter.y;
		data->ray[index].is_open = 1;
	}
	if (is_wall(*data, next_inter.x, next_inter.y))
	{
		set_value(wall, next_inter.x, next_inter.y);
		return (0);
	}
	else if (hit_door(data, next_inter.x, next_inter.y))
	{
		set_value(wall, next_inter.x, next_inter.y);
		data->ray[index].is_door = 1;
		return (0);
	}
	return (1);
}

void	check_horz_hitwall(t_data *data, int index, t_coordinate inter,
		t_coordinate step)
{
	t_coordinate	next_inter;
	t_coordinate	wall;

	set_value(&wall, 0, 0);
	set_value(&next_inter, inter.x, inter.y);
	data->ray[index].is_door = 0;
	data->ray[index].is_open = 0;
	if (ray_up(data->ray[index]))
		next_inter.y -= 0.00001;
	while (next_inter.x >= 0 && next_inter.x < (data->width * SCALE)
		&& next_inter.y >= 0 && next_inter.y < (data->height * SCALE))
	{
		if (is_last_inter_horz(data, index, next_inter, &wall) == 0)
			break ;
		set_value(&next_inter, next_inter.x + step.x, next_inter.y + step.y);
	}
	data->ray[index].wall_inter_x = wall.x;
	data->ray[index].wall_inter_y = wall.y;
	data->ray[index].distance = distance_2points(data->player.x, data->player.y,
			wall.x, wall.y);
	data->ray[index].direction = 'h';
}

void	first_h_inter(int index, t_data *data)
{
	t_coordinate	inter;
	t_coordinate	step;

	inter.x = 0;
	inter.y = 0;
	step.x = 0;
	step.y = 0;
	inter.y = (int)floor(data->player.y / SCALE) * SCALE;
	if (ray_down(data->ray[index]))
		inter.y += (SCALE);
	inter.x = data->player.x + (inter.y - data->player.y)
		/ tan(data->ray[index].ray_angle);
	step.y = SCALE;
	if (ray_up(data->ray[index]))
		step.y *= -1;
	step.x = SCALE / tan(data->ray[index].ray_angle);
	if (ray_right(data->ray[index]) && step.x < 0)
		step.x *= -1;
	if (ray_left(data->ray[index]) && step.x > 0)
		step.x *= -1;
	check_horz_hitwall(data, index, inter, step);
}
