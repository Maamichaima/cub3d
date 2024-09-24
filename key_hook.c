/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:01:22 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/22 23:51:32 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int key_hook(t_data *x)
{
	double x_x;
	double y_y;
	int f;
	int h;

	mlx_clear_window(x->mlx_ptr, x->mlx_win);
	if(x->keys[W])
	{
		x_x = x->player.x + (x->player.dx * P_SPEED);
		y_y = x->player.y + (x->player.dy * P_SPEED);
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(x->keys[S])
	{
		x_x = x->player.x - x->player.dx * P_SPEED;
		y_y = x->player.y - x->player.dy * P_SPEED;
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(x->keys[D])
	{
		y_y = x->player.y + x->player.dx * P_SPEED;
		x_x = x->player.x - x->player.dy * P_SPEED;
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(x->keys[A])
	{
		y_y = x->player.y - x->player.dx * P_SPEED;
		x_x = x->player.x + x->player.dy * P_SPEED;
		h = x_x / SCALE;
		f = y_y / SCALE;
		if(x->map[f][h] == '0')
		{
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	if(x->keys[R])
	{
		x->player.angle += A_SPEED;
		x->player.dx = cos(x->player.angle);
		x->player.dy = sin(x->player.angle);
	}
	if(x->keys[L])
	{
		x->player.angle -= A_SPEED;
		x->player.dx = cos(x->player.angle);
		x->player.dy = sin(x->player.angle);
	}
	// draw(*x);
	return 0;
}
