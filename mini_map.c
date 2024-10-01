/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:53:33 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/01 19:07:19 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void cast_ray_mini_map(t_data *x)
{
	int i = 0;
	
	while(i < x->num_rays)
    {
		draw_ray(x, x->player.x, x->player.y, x->ray[i]);
    	// draw_line_angle(x, x0,y0);
    //     id_column++;
        i++;
    }
}

void mini_map(t_data *x, double scale)
{
	double a;
	double b;
	double i = 0;
	double j = 0;
	
	while(i < (x->height * scale))
	{
		j = 0;
		while(j < (x->width * scale))
		{
			a = i / scale;
			b = j / scale;
			if((int)i % (int)scale == 0 || (int)j % (int)scale == 0)
				my_mlx_pixel_put(x, j, i, 0x000000);
			else if (a >= 0 && a < x->height && b >= 0 && b < x->width && x->map[(int)a][(int)b] == '1')
            	my_mlx_pixel_put(x, j, i, 0xe0d5d9);
			else if(a >= 0 && a < x->height && b >= 0 && b < x->width && x->map[(int)a][(int)b] == '0')
            	my_mlx_pixel_put(x, j, i, 0x215dbf);
			j++;
		}
		i++;
	}
	color_one_square((x->player.x / SCALE) - scale / 2, (x->player.y / SCALE) - scale / 2, x, scale);
}
