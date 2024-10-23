/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:30:53 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/23 19:48:22 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	*x_mouse(void)
{
	static int	x = 0;

	return (&x);
}

int	mouse_move(int x, int y, t_data *data)
{
	int static	c;

	if (c == 0)
	{
		*x_mouse() = x;
		c = 1;
	}
	if (x > *x_mouse())
	{
		data->player.angle += A_SPEED;
		if (data->player.angle >= 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dx = cos(data->player.angle);
		data->player.dy = sin(data->player.angle);
	}
	if (x < *x_mouse())
	{
		data->player.angle -= A_SPEED;
		if (data->player.angle < 0)
			data->player.angle = 2 * PI - data->player.angle;
		data->player.dx = cos(data->player.angle);
		data->player.dy = sin(data->player.angle);
	}
	*x_mouse() = x;
	return (0);
}
