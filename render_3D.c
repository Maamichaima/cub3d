/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:34:11 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/07 21:19:29 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double dmod(double x, double y) {
    return x - (long long)(x/y) * y;
}

// void draw_rect(t_data *data, double wall_height, int j, int color)
// {
// 	int i = (data->height * SCALE / 2) - wall_height / 2;
// 	if( wall_height > (data->height * SCALE / 2) + wall_height / 2)
// 		wall_height = (data->height * SCALE / 2) + wall_height / 2;
// 	while(i < (data->height * SCALE / 2) + wall_height / 2)
// 	{
// 		if(i >= 0 && i < data->height * SCALE)
// 			my_mlx_pixel_put(data, j, i, color);
// 		i++;
// 	}
// }

void draw_rect(t_data *data, double wall_height, int j, int color)
{
	int	lim = (HEIGHT / 2) + wall_height / 2;
	int i = (HEIGHT / 2) - wall_height / 2;
	// if (lim > HEIGHT)
	// 	lim = HEIGHT;
	// printf("%f \n", wall_height);
	while(i < lim)
	{
		if(i >= 0 && i < HEIGHT)
			my_mlx_pixel_put(data, j, i, color);
		i++;
	}
}

// void draw_rect(t_data *data, double wall_height, int j, int color)
// {
// 	int i = 0;
// 	// while(i < (data->height * SCALE / 2) - wall_height / 2)
// 	// {	
// 	// 	if(i >= 0 && i < data->height * SCALE)
// 	// 		my_mlx_pixel_put(data, j, i, 0x34baeb);
// 	// 	i++;
// 	// }
// 	i = (HEIGHT / 2) - wall_height / 2;//(data->height * SCALE / 2) - wall_height / 2;
// 	if( wall_height > (HEIGHT / 2) + wall_height / 2)
// 		wall_height = (HEIGHT / 2) + wall_height / 2;
// 	while(i < (HEIGHT / 2) + wall_height / 2)
// 	{
// 		if(i >= 0 && i < HEIGHT)
// 			my_mlx_pixel_put(data, j, i, color);
// 		i++;
// 	}
	
// 	// while(i < data->height * SCALE)
// 	// {
// 	// 	if(i >= 0 && i < data->height * SCALE)
// 	// 		my_mlx_pixel_put(data, j, i,0xeb6b34);
// 	// 	i++;
// 	// }
// }

int set_wall_color(t_ray ray, double player_angle)
{
    if (ray.direction == 'h')
    {
        // if (ray.ray_angle > 0 && ray.ray_angle < PI) 
        //     return 0xD239FF;
        // else 
            return 0xFF25CD;
    }
    else if (ray.direction == 'v')
	{
        // if (ray.ray_angle < (PI / 2) || ray.ray_angle > 3 * (PI / 2))
        //     return 0x66D7FF;
        // else 
            return 0xFFF666;
    }
	return (0);
}

void draw_line_of_tex(t_data *data, double wall_height, double j)
{
	double scale_width;
	double scale_height;
	int	lim = (HEIGHT / 2) + wall_height / 2;
	int i = (HEIGHT / 2) - wall_height / 2;
	double a, b;
	
	// if (lim > HEIGHT)
	// 	lim = HEIGHT;
	// if (i < 0)
	// 	i = 0;
    // data->texture->ptr_img = mlx_xpm_file_to_image(data->mlx_ptr, "texture->xpm",&data->texture->width,&data->texture->height);
	// data->texture->img.addr = mlx_get_data_addr(data->texture->ptr_img, &data->texture->img.bits_per_pixel, &data->texture->img.line_length, &data->texture->img.endian);
    scale_height = wall_height / data->texture->height;
    scale_width = wall_height / data->texture->width;
	if(!data->texture->ptr_img)
        printf("Image reading has failed \n");
	unsigned int color;
	double	d = (long long)data->ray[(long long)j].wall_inter_X / SCALE * SCALE;
	d = data->ray[(long long)j].wall_inter_X - d;
	a = dmod((j + d) / scale_width, data->texture->width);
	// printf("%d \n", i);
	while(i < lim)
	{
		b = dmod((i - ((HEIGHT / 2) - wall_height / 2)) / scale_height, data->texture->height);
		color = 0;
		if(a < data->texture->width && a >= 0 && b < data->texture->height && b >= 0)
			color = my_mlx_pixel_get(data->texture->img, a, b);
		if(i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH)
			my_mlx_pixel_put(data, j, i, color);
		i++;
	}
}


void render_projected_wall(t_data *data)
{
	double i = 0;
	int j = 0;
	double d_projection_plane;
	double wall_height;
	int color = 0;
	double correct_wall_distance;
	while(i < WIDTH)//(data->width * SCALE))
	{
		j = 0;
		while( j < HEIGHT)//(data->height * SCALE) )
		{	
			if(j < HEIGHT / 2)//(data->height  * SCALE / 2))
				my_mlx_pixel_put(data, i, j, 0x34baeb);
			else if(j > HEIGHT / 2)//(data->height  * SCALE / 2))
				my_mlx_pixel_put(data, i, j, 0xeb6b34);
			j++;
		}
		i++;
	}
	i = 0;
	while(i < data->num_rays)
	{
		d_projection_plane = (WIDTH / 2) / tan(FOV /2);//(data->width * SCALE / 2) / tan(FOV /2);
		correct_wall_distance =  data->ray[(long long)i].distance * cos( data->ray[(long long)i].ray_angle - data->player.angle);
		wall_height = (SCALE / correct_wall_distance) * d_projection_plane;
		// color = set_wall_color(data->ray[(int)i], data->player.angle);
		// draw_rect(data, wall_height, i, color);
		draw_line_of_tex(data, wall_height, i);
		i++;
	}
}
