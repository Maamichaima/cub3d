/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:53:33 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/03 00:19:47 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void cast_ray_mini_map(t_data *x)
{
	int i = 0;
	
	while(i < x->num_rays)
    {
		draw_ray(x, x->player.x , x->player.y, x->ray[i]);
		// printf("%f   %f   \n", x->player.angle, x->ray[i].ray_angle);
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
	(void) scale;
	
	while(i < (x->height * SCALE))
	{
		j = 0;
		while(j < (x->width * SCALE))
		{
			a = i / SCALE;
			b = j / SCALE;
			// if((int)i % (int)SCALE  == 0 || (int)j % (int)SCALE == 0)
			// 	my_mlx_pixel_put(x,j, i, 0x000000);
			if (a >= 0 && a < x->height && b >= 0 && b < x->width && x->map[(int)a][(int)b] == '1')
            	my_mlx_pixel_put(x, MINIMAP_SCALE *j, MINIMAP_SCALE * i, 0xe0d5d9);
			else if(a >= 0 && a < x->height && b >= 0 && b < x->width && x->map[(int)a][(int)b] == '0')
            	my_mlx_pixel_put(x, MINIMAP_SCALE *j,MINIMAP_SCALE *  i, 0x215dbf);
			j++;
		}
		i++;
	}
	color_one_square((x->player.x) - SCALE / 2, (x->player.y) - SCALE / 2, x, SCALE);
	//cast_ray_mini_map(x);
	draw_line_angle(x, x->player.x * MINIMAP_SCALE, x->player.y * MINIMAP_SCALE);
}
