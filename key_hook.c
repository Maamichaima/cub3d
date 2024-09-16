/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:01:22 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/15 17:01:26 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int key_hook(int key, t_data *x)
{
	double x_x;
	double y_y;
	int f;
	int h;

	mlx_clear_window(x->mlx_ptr, x->mlx_win);
	if(key == XK_w)
	{
		x_x = x->player.x + (x->player.dx * 5);
		y_y = x->player.y + (x->player.dy * 5);
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(key == XK_s)
	{
		x_x = x->player.x - x->player.dx * 10;
		y_y = x->player.y - x->player.dy * 10;
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(key == XK_d)
	{
		y_y = x->player.y + x->player.dx * 10;
		x_x = x->player.x - x->player.dy * 10;
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(key == XK_a)
	{
		y_y = x->player.y - x->player.dx * 10;
		x_x = x->player.x + x->player.dy * 10;
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(key == XK_Right)
	{
		x->player.angle += PI / 10;
		x->player.dx = cos(x->player.angle);
		x->player.dy = sin(x->player.angle);
	}
	if(key == XK_Left)
	{
		x->player.angle -= PI / 10;
		x->player.dx = cos(x->player.angle);
		x->player.dy = sin(x->player.angle);
	}
	draw(*x);
	return 0;
}
