/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:45:54 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/22 15:31:36 by maamichaima      ###   ########.fr       */
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
	
	while(i < (HEIGHT))
	{
		j = 0;
		while(j < WIDTH)
		{
			my_mlx_pixel_put(x, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int draw(t_data *data)
{
	int x, y;
	
	// mlx_mouse_get_pos(data->mlx_ptr, &x, &y);
	// mouse_move(x, y, data);
	clear_img(data);
	key_hook(data);
	cast_ray(data, data->player.x, data->player.y);
	render_projected_wall(data);
	animation(data);
	mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->image.ptr_img, 0, 0);
	return 0;
} 
