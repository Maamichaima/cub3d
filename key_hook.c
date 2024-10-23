/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:01:22 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/23 16:09:20 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	*move(void)
{
	static int	x = 0;

	return (&x);
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
