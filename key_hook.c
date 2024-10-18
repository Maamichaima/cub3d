/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:01:22 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/18 16:42:38 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void slide_w(t_data *data)
{
	double slide_x = data->player.x + (data->player.dx * P_SPEED);
	double slide_y = data->player.y;
	int f;
	int h;

	h = slide_x / SCALE;
	f = slide_y / SCALE;
	if(data->map[f][h] == '0')
	{
		// printf("herekna x\n");
		data->player.x = slide_x;
	}
	else
	{
		slide_x = data->player.x;
		slide_y = data->player.y + (data->player.dy * P_SPEED);
		h = slide_x / SCALE;
		f = slide_y / SCALE;
		if(data->map[f][h] == '0')
		{
			// printf("herekna y\n");
			data->player.y = slide_y;
		}
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

int key_hook(t_data *x)
{
	double x_x;
	double y_y;
	int f;
	int h;

	mlx_clear_window(x->mlx_ptr, x->mlx_win);
	if(x->keys[ESC] == 1)
		exit (0);
	
	if(x->keys[W])
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
        else
			slide_w(x);
	}
	if(x->keys[S])
    {
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
    if(x->keys[D])
    {
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
    if(x->keys[A])
    {
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
	if(x->keys[R])
	{
		x->player.angle += A_SPEED;
		if(x->player.angle >= 2 * PI)
			x->player.angle -= 2 * PI;
		x->player.dx = cos(x->player.angle);
		x->player.dy = sin(x->player.angle);
	}
	if(x->keys[L])
	{
		x->player.angle -= A_SPEED;
		if(x->player.angle < 0)
			x->player.angle = 2 * PI - x->player.angle;
		x->player.dx = cos(x->player.angle);
		x->player.dy = sin(x->player.angle);
	}
	// draw(*x);
	return 0;
}
