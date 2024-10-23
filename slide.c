/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:03:57 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/23 17:16:08 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	check_distance(t_data *x)
{
	return (Distance_2Points(x->player.x, x->player.y
		, x->ray[WIDTH / 2].wall_inter_x, x->ray[WIDTH / 2].wall_inter_y) >= P_DISTANCE);
}

void slide_w(t_data *data)
{
	double slide_x = data->player.x + (data->player.dx * P_SPEED);
	double slide_y = data->player.y;
	int f;
	int h;

	h = slide_x / SCALE;
	f = slide_y / SCALE;
	if(data->ray[WIDTH / 2].direction == 'h' && data->map[f][h] == '0')
		data->player.x = slide_x;
	else
	{
		slide_x = data->player.x;
		slide_y = data->player.y + (data->player.dy * P_SPEED);
		h = slide_x / SCALE;
		f = slide_y / SCALE;
		if(data->ray[WIDTH / 2].direction == 'v' && data->map[f][h] == '0')
			data->player.y = slide_y;
	}
}

void slide_s(t_data *data)
{
	double slide_x = data->player.x - (data->player.dx * P_SPEED);
	double slide_y = data->player.y;
	int f;
	int h;

	h = slide_x / SCALE;
	f = slide_y / SCALE;
	if(data->map[f][h] == '0')
		data->player.x = slide_x;
	else
	{
		slide_x = data->player.x;
		slide_y = data->player.y - (data->player.dy * P_SPEED);
		h = slide_x / SCALE;
		f = slide_y / SCALE;
		if(data->map[f][h] == '0')
			data->player.y = slide_y;
	}
}

void slide_d(t_data *data)
{
	double slide_x = data->player.x - (data->player.dy * P_SPEED);
	double slide_y = data->player.y;
	int f;
	int h;

	h = slide_x / SCALE;
	f = slide_y / SCALE;
	if(data->map[f][h] == '0')
		data->player.x = slide_x;
	else
	{
		slide_x = data->player.x;
		slide_y = data->player.y + (data->player.dx * P_SPEED);
		h = slide_x / SCALE;
		f = slide_y / SCALE;
		if(data->map[f][h] == '0')
			data->player.y = slide_y;
	}
}

void slide_a(t_data *data)
{
	double slide_x = data->player.x + (data->player.dy * P_SPEED);
	double slide_y = data->player.y;
	int f;
	int h;

	h = slide_x / SCALE;
	f = slide_y / SCALE;
	if(data->map[f][h] == '0')
		data->player.x = slide_x;
	else
	{
		slide_x = data->player.x;
		slide_y = data->player.y - (data->player.dx * P_SPEED);
		h = slide_x / SCALE;
		f = slide_y / SCALE;
		if(data->map[f][h] == '0')
			data->player.y = slide_y;
	}
}
