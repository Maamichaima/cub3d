/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:34:11 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/01 13:05:38 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void draw_rect(t_data *data, double wall_height, int j)
{
	int i = (data->height * SCALE / 2) - wall_height / 2;
	while(i < (data->height * SCALE / 2) + wall_height / 2)
	{
		if(i >= 0 && i < data->height * SCALE)
			my_mlx_pixel_put(data, j, i, 0XFFFFFF);
		i++;
	}
}

void rander_prijected_wall(t_data *data)
{
	double i = 0;
	double d_projection_plane;
	double wall_height;

	while(i < data->num_rays)
	{
		d_projection_plane = (data->width * SCALE / 2) / tan(FOV /2);
		wall_height = (SCALE / data->ray[(int)i].distance) * d_projection_plane;
		draw_rect(data, wall_height, i);
		i++;
	}
}
