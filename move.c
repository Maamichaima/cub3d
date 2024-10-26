/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:08:19 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/23 16:09:31 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	move_w(t_data *x)
{
	double	x_x;
	double	y_y;
	int		f;
	int		h;
	pthread_t tid;

	if (check_distance(x))
	{
		x_x = x->player.x + (x->player.dx * P_SPEED);
		y_y = x->player.y + (x->player.dy * P_SPEED);
		h = x_x / SCALE;
		f = y_y / SCALE;
		if (x->map[f][h] == '0' || x->map[f][h] == 'O')
		{
			if(x->sound_flag)
			{
				pthread_create(&tid, NULL, play_sound, x);
				pthread_detach(tid);
			}
			x->player.x = x_x;
			x->player.y = y_y;
		}
	}
	else
		slide_w(x);
}

void	move_s(t_data *x)
{
	double	x_x;
	double	y_y;
	int		f;
	int		h;

	x_x = x->player.x - (x->player.dx * P_SPEED);
	y_y = x->player.y - (x->player.dy * P_SPEED);
	h = x_x / SCALE;
	f = y_y / SCALE;
	if (x->map[f][h] == '0' || x->map[f][h] == 'O')
	{
		x->player.x = x_x;
		x->player.y = y_y;
	}
	else
		slide_s(x);
}

void	move_d(t_data *x)
{
	double	x_x;
	double	y_y;
	int		f;
	int		h;

	x_x = x->player.x - (x->player.dy * P_SPEED);
	y_y = x->player.y + (x->player.dx * P_SPEED);
	h = x_x / SCALE;
	f = y_y / SCALE;
	if (x->map[f][h] == '0' || x->map[f][h] == 'O')
	{
		x->player.x = x_x;
		x->player.y = y_y;
	}
	else
		slide_d(x);
}

void	move_a(t_data *x)
{
	double	x_x;
	double	y_y;
	int		f;
	int		h;

	x_x = x->player.x + (x->player.dy * P_SPEED);
	y_y = x->player.y - (x->player.dx * P_SPEED);
	h = x_x / SCALE;
	f = y_y / SCALE;
	if (x->map[f][h] == '0' || x->map[f][h] == 'O')
	{
		x->player.x = x_x;
		x->player.y = y_y;
	}
	else
		slide_a(x);
}
