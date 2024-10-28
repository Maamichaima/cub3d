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

void	cast_ray(t_data *x)
{
	int		id_column;
	int		i;
	double	ray_angle;

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
}
