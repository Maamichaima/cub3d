/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:30:25 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 13:59:27 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	set_flag_close(double *closet_distance, int i, t_ray ray, int *flag)
{
	double	current_distance;

	current_distance = ray.distance;
	if (current_distance < *closet_distance)
	{
		*closet_distance = current_distance;
		*flag = i;
	}
}

void	set_flag_open(double *open_distance, t_data x, int i, int *flag1)
{
	double	distance;

	distance = distance_2points(x.player.x, x.player.y, x.ray[i].x, x.ray[i].y);
	if (distance < *open_distance)
	{
		*open_distance = distance;
		*flag1 = i;
	}
}

void	door_keys(t_data *x)
{
	int		i;
	int		flag;
	int		flag1;
	double	closet_distance;
	double	open_distance;

	i = 0;
	closet_distance = INT_MAX;
	open_distance = INT_MAX;
	flag = -1;
	flag1 = -1;
	while (i < x->num_rays)
	{
		if (x->ray[i].is_door)
			set_flag_close(&closet_distance, i, x->ray[i], &flag);
		else if (x->ray[i].is_open)
			set_flag_open(&open_distance, *x, i, &flag1);
		i++;
	}
	if (x->keys[O] && flag != -1 && closet_distance < 250)
		set_o_in_map(x, flag);
	if (x->keys[C] && flag1 != -1 && open_distance < 250)
		set_d_in_map(x, flag1);
	x->keys[C] = 0;
	x->keys[O] = 0;
}

void	cast_ray(t_data *x, int x0, int y0)
{
	int		id_column;
	int		i;
	double	ray_angle;
	double	d_v;
	double	d_h;

	id_column = 0;
	i = 0;
	ray_angle = x->player.angle - (FOV / 2);
	x->ray[i].ray_angle = protect_angle(ray_angle);
	while (i < x->num_rays)
	{
		if (i != 0)
		{
			x->ray[i].ray_angle = x->ray[i - 1].ray_angle + FOV / x->num_rays;
			x->ray[i].ray_angle = protect_angle(x->ray[i].ray_angle);
		}
		first_h_inter(i, x);
		first_v_inter(i, x);
		i++;
	}
	door_keys(x);
}
