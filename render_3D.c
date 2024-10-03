/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:34:11 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/02 23:56:07 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void draw_rect(t_data *data, double wall_height, int j, int color)
{
	int i = (data->height * SCALE / 2) - wall_height / 2;
	if( wall_height > (data->height * SCALE / 2) + wall_height / 2)
		wall_height = (data->height * SCALE / 2) + wall_height / 2;
	while(i < (data->height * SCALE / 2) + wall_height / 2)
	{
		if(i >= 0 && i < data->height * SCALE)
			my_mlx_pixel_put(data, j, i, color);
		i++;
	}
}

int set_wall_color(t_ray ray, double player_angle)
{
    if (ray.direction == 'h')
    {
        if (ray.ray_angle > 0 && ray.ray_angle < PI) 
            return 0xD239FF;
        else 
            return 0xFF25CD;
    }
    else if (ray.direction == 'v')
	{
        if (ray.ray_angle < (PI / 2) || ray.ray_angle > 3 * (PI / 2))
            return 0x66D7FF;
        else 
            return 0xFFF666;
    }
	return (0);
}

void render_projected_wall(t_data *data)
{
	double i = 0;
	double d_projection_plane;
	double wall_height;
	int color;
	double correct_wall_distance;

	while(i < data->num_rays)
	{
		d_projection_plane = (data->width * SCALE / 2) / tan(FOV /2);
		correct_wall_distance =  data->ray[(int)i].distance * cos( data->ray[(int)i].ray_angle - data->player.angle );
		wall_height = (SCALE / correct_wall_distance) * d_projection_plane;
		color = set_wall_color(data->ray[(int)i], data->player.angle);
		draw_rect(data, wall_height, i, color);
		i++;
	}
}
