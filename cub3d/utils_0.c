/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:45:56 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 14:43:26 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double	protect_angle(double angle)
{
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	while (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	distance_2points(double x, double y, double x_wall, double y_wall)
{
	if (x_wall == 0 && y_wall == 0)
		return (INT_MAX);
	return (sqrt(((x_wall - x) * (x_wall - x)) + ((y_wall - y) * (y_wall
					- y))));
}

void	set_value(t_coordinate *c, double x, double y)
{
	c->x = x;
	c->y = y;
}

void	set_o_in_map(t_data *x, int flag)
{
	x->map[(int)x->ray[flag].wall_inter_y
		/ SCALE][(int)x->ray[flag].wall_inter_x / SCALE] = 'O';
}

void	set_d_in_map(t_data *x, int flag1)
{
	x->map[(int)x->ray[flag1].y / SCALE][(int)x->ray[flag1].x / SCALE] = 'd';
}
