/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:01:22 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/22 20:40:28 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	check_distance(t_data *x)
{
	return (Distance_2Points(x->player.x, x->player.y
		, x->ray[WIDTH / 2].wall_inter_X, x->ray[WIDTH / 2].wall_inter_Y) >= P_DISTANCE);
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

int	*move(void)
{
	static int	x = 0;

	return (&x);
}

void move_w(t_data *x)
{
	double x_x;
	double y_y;
	int f;
	int h;
	
	if (check_distance(x))
	{
		x_x = x->player.x + (x->player.dx * P_SPEED);
		y_y = x->player.y + (x->player.dy * P_SPEED);
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0' || x->map[f][h] == 'O')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	else
		slide_w(x);
}

void move_s(t_data *x)
{
	double x_x;
	double y_y;
	int f;
	int h;
	
	x_x = x->player.x - (x->player.dx * P_SPEED);
	y_y = x->player.y - (x->player.dy * P_SPEED);
	h = x_x / SCALE;
	f = y_y / SCALE;

	if(x->map[f][h] == '0' || x->map[f][h] == 'O')
	{
		x->player.x = x_x;
		x->player.y = y_y;
	}
	else
		slide_s(x);
}

void move_d(t_data *x)
{
	double x_x;
	double y_y;
	int f;
	int h;
	
	x_x = x->player.x - (x->player.dy * P_SPEED);
	y_y = x->player.y + (x->player.dx * P_SPEED);
	h = x_x / SCALE;
	f = y_y / SCALE;
	if(x->map[f][h] == '0' || x->map[f][h] == 'O')
	{
		x->player.x = x_x;
		x->player.y = y_y;
	}
	else
		slide_d(x);
}

void move_a(t_data *x)
{
	double x_x;
	double y_y;
	int f;
	int h;
	
	x_x = x->player.x + (x->player.dy * P_SPEED);
	y_y = x->player.y - (x->player.dx * P_SPEED);
	h = x_x / SCALE;
	f = y_y / SCALE;
	if(x->map[f][h] == '0' || x->map[f][h] == 'O')
	{
		x->player.x = x_x;
		x->player.y = y_y;
	}
	else
		slide_a(x);
}

void move_r(t_data *x)
{
	x->player.angle += A_SPEED;
	if(x->player.angle >= 2 * PI)
		x->player.angle -= 2 * PI;
	x->player.dx = cos(x->player.angle);
	x->player.dy = sin(x->player.angle);
}

void move_l(t_data *x)
{
	x->player.angle -= A_SPEED;
	if(x->player.angle < 0)
		x->player.angle = 2 * PI - x->player.angle;
	x->player.dx = cos(x->player.angle);
	x->player.dy = sin(x->player.angle);
}

int key_hook(t_data *x)
{
	mlx_clear_window(x->mlx_ptr, x->mlx_win);
	if(x->keys[ESC])
		exit (0);
	if(x->keys[W])
		move_w(x);
	if(x->keys[S])
		move_s(x);
    if(x->keys[D])
		move_d(x);
    if(x->keys[A])
		move_a(x);
	if(x->keys[R])
		move_r(x);
	if(x->keys[L])
		move_l(x);
	return 0; 
}
