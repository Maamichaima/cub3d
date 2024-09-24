/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:45:54 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/24 22:00:47 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void color_one_square(int start_x, int start_y, void *x)
{
    int i = 0;
	int j = 0;
	int s_x = start_x + SCALE /2;
	int s_y = start_y + SCALE /2;
    int color = 0xf54242;

    while (i < SCALE)
    {
		j = 0;
        while (j < SCALE)
        {
			// printf("%d   %d \n", i, j);
			if(i < (SCALE - 10) && j < (SCALE - 10) && i > 10 && j > 10)
            	my_mlx_pixel_put(x, start_x + i, start_y + j, color);
			j++;
        }
		i++;
    }
}

int center_x = 15;
int center_y = 15;
void put_mini_cyrcle(t_data x, int j, int i)
{
	int r;

	printf("%d   %d   \n", center_x, center_y);
	if((i - center_x) * (i - center_x) + (j - center_y) * (j - center_y) <= (x.rayon * x.rayon))
	{
		puts("hh");
		my_mlx_pixel_put(&x, j, i, 0xf54242);
	}
}

void draw_line_angle(t_data *data, int x0, int y0)
{
	int x , y;
	int i;

	i = 0;
	while (i < LIGNE_OF_PLAYER)
	{
		x = x0 + i * cos(data->ray.ray_angle);
		y = y0 + i * sin(data->ray.ray_angle);
		if(x >= 0 && x < data->width * SCALE && y < data->height * SCALE && y >= 0)
			my_mlx_pixel_put(data, x, y, 0xFFF344);
		i++;
	}
}

void draw_ray_angel(t_data *x)
{
	int i;
	
	x->ray.ray_angle = x->player.angle - (FOV_ANGLE / 2);
	i = 0;
	while(i < x->ray.num_rays)
	{
		x->ray.ray_angle += FOV_ANGLE / x->ray.num_rays;
		draw_line_angle(x, x->player.x, x->player.y);
		i++;
	}
}

int draw(t_data *x)
{
	double i = 0;
	double j = 0;
	double a;
	double b;

	key_hook(x);
	while(i < (x->height * SCALE))
	{
		j = 0;
		while(j < (x->width * SCALE))
		{
			a = i / SCALE;
			b = j / SCALE;
			
			if(a >= 0 && a < x->height && b >= 0 && b < x->width && x->map[(int)a][(int)b] == '1')
            	my_mlx_pixel_put(x, j, i, 0xe0d5d9);
			else if(a >= 0 && a < x->height && b >= 0 && b < x->width && x->map[(int)a][(int)b] == '0')
            	my_mlx_pixel_put(x, j, i, 0x215dbf);
			j++;
		}
		i++;
	}
	// my_mlx_pixel_put(&x, x->player.x, x->player.y, 0xf54242); // draw just player
	color_one_square(x->player.x - SCALE / 2, x->player.y - SCALE / 2, x);
	draw_ray_angel(x);
	// x->ray.ray_angle = x->player.angle;// - (FOV_ANGLE / 2);
	// draw_line_angle(x, x->player.x, x->player.y);
	mlx_put_image_to_window(x->mlx_ptr, x->mlx_win, x->image.ptr_img, 0, 0);
	return 0;
}
