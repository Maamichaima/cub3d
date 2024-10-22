/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:45:54 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/14 16:11:54 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void color_one_square(int start_x, int start_y, void *x,  double scale)
{
    int i = 0;
	int j = 0;
	double s_x = start_x - MINIMAP_SCALE / 2;
	double s_y = start_y - MINIMAP_SCALE / 2;
    int color = 0xf54242;

	// printf(" %d   %f   %d   %f \n", start_x, (s_x + i), start_y, (s_y + j));
	// my_mlx_pixel_put(x, s_x, s_x, 0xf54242);
	// my_mlx_pixel_put(x, s_x + MINIMAP_SCALE, s_x + MINIMAP_SCALE, 0xf54242);
    while (i <= MINIMAP_SCALE)
    {
		j = 0;
        while (j <= MINIMAP_SCALE)
        {
			// printf("%d   %d \n", start_x, start_y);
			if(i <= (MINIMAP_SCALE - 3) && j <= (MINIMAP_SCALE - 3 ) && i >= 3 && j >= 3)
			{
				// puts("hhh");
            	my_mlx_pixel_put(x, (s_x + i), (s_y + j), color);
			}
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
		my_mlx_pixel_put(&x, j, i, 0xf54242);
	}
}

void draw_line_angle(t_data *data, int x0, int y0)
{
	int x, y;
	int i;

	i = 0;
	while (i < LIGNE_OF_PLAYER)
	{
		x = x0 + i * cos(data->player.angle);
		y = y0 + i * sin(data->player.angle);
		if(x >= 0 && y >= 0)
			my_mlx_pixel_put(data, x, y, 0xff0000);
		i++;
	}
}

void clear_img(t_data *x)
{
	double i = 0;
	double j = 0;
	
	while(i < (HEIGHT))//x->height * SCALE
	{
		j = 0;
		while(j < WIDTH)//(x->width * SCALE))
		{
			my_mlx_pixel_put(x, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int draw(t_data *x)
{
	double i = 0;
	double j = 0;
	double a;
	double b;

	clear_img(x);
	key_hook(x);
	//color_one_square(x->player.x - SCALE / 2, x->player.y - SCALE / 2, x);
	// draw_line_angle(x, x->player.x, x->player.y);
	cast_ray(x, x->player.x, x->player.y);
	// implement_door_status(x,x->ray[WIDTH / 2]);
	render_projected_wall(x);
	mini_map(x);
	// draw_ray(x, x->player.x, x->player.y);
	// printf("%f %f \n", x->player.x, x->player.y); 
	mlx_put_image_to_window(x->mlx_ptr, x->mlx_win, x->image.ptr_img, 0, 0);
	return 0;
} 
