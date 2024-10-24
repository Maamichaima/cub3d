/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:44:38 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 14:05:16 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_last_inter_verti(t_data *data, int index, t_coordinate next_inter,
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
		wall->x = next_inter.x;
		wall->y = next_inter.y;
		return (-1);
	}
	else if (hit_door(data, index, next_inter.x, next_inter.y))
	{
		wall->x = next_inter.x;
		wall->y = next_inter.y;
		return (0);
	}
	return (1);
}

void	compare_distance(t_data *data, t_coordinate wall, int index,
		int is_door)
{
	double	vert_distance;

	vert_distance = distance_2points(data->player.x, data->player.y, wall.x,
			wall.y);
	if (vert_distance < data->ray[index].distance)
	{
		data->ray[index].distance = vert_distance;
		data->ray[index].wall_inter_x = wall.x;
		data->ray[index].wall_inter_y = wall.y;
		data->ray[index].direction = 'v';
		data->ray[index].is_door = is_door;
	}
}

void	check_vert_hitwall(t_data *data, int index, t_coordinate inter,
		t_coordinate step)
{
	t_coordinate	next_inter;
	t_coordinate	wall;
	int				is_door;

	is_door = 0;
	set_value(&wall, 0, 0);
	set_value(&next_inter, inter.x, inter.y);
	if (ray_left(data->ray[index]))
		next_inter.x -= 0.00001;
	while (next_inter.x >= 0 && next_inter.x < (data->width * SCALE)
		&& next_inter.y >= 0 && next_inter.y < (data->height * SCALE))
	{
		if (is_last_inter_verti(data, index, next_inter, &wall) == 0)
		{
			is_door = 1;
			break ;
		}
		else if (is_last_inter_verti(data, index, next_inter, &wall) == -1)
			break ;
		set_value(&next_inter, next_inter.x + step.x, next_inter.y + step.y);
	}
	compare_distance(data, wall, index, is_door);
}

void	first_v_inter(int index, t_data *data)
{
	t_coordinate	inter;
	t_coordinate	step;

	inter.x = 0;
	inter.y = 0;
	step.x = 0;
	step.y = 0;
	inter.x = (int)floor(data->player.x / SCALE) * SCALE;
	if (ray_right(data->ray[index]))
		inter.x += (SCALE);
	inter.y = data->player.y + ((inter.x - data->player.x)
			* tan(data->ray[index].ray_angle));
	step.x = SCALE;
	if (ray_left(data->ray[index]))
		step.x *= -1;
	step.y = (SCALE * tan(data->ray[index].ray_angle));
	if (ray_up(data->ray[index]) && step.y > 0)
		step.y *= -1;
	if (ray_down(data->ray[index]) && step.y < 0)
		step.y *= -1;
	check_vert_hitwall(data, index, inter, step);
}
