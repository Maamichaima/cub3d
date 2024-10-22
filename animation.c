/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:14:00 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/21 15:58:22 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void    animation(t_data *data)
{
	double scale_width;
	double scale_height;
	t_texture t;
	int i = 0;
	int j = 300;
	double a, b;
	
	t = data->animation[data->ff];
    scale_height = HEIGHT / (double)t.height;
    scale_width = WIDTH / (double)t.width;
	int color;
	while(i < WIDTH)
	{
		j = 0;
		while(j < HEIGHT)
		{
			a = i / scale_width;
			b = j / scale_height;
			color = my_mlx_pixel_get(t.img, a, b);
			if(color > 0 && i > 0 && i < WIDTH && j > 0 && j < HEIGHT)
				my_mlx_pixel_put(data, i, j, color);
			j++;
		}
		i++;
	}
	data->ff++;
	if(data->ff == 21)
		data->ff = 0;
	else if(data->ff == 91)
		data->ff = 0;
}
