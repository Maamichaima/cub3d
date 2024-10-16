/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:34:11 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/16 01:22:41 by cmaami           ###   ########.fr       */
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

double get_start_text(t_ray ray, t_texture tex)
{
	double	d;
	
	if (ray.direction == 'h')
	{
		d = (long long)ray.wall_inter_X / SCALE * SCALE;
		d = (ray.wall_inter_X - d) / SCALE * tex.width;
	}
	else
	{
		d = (long long)ray.wall_inter_Y / SCALE * SCALE;
		d = (ray.wall_inter_Y - d) / SCALE * tex.width;
	}
	return d;
}

t_texture hh(t_texture *t, char *str)
{
	while(t)
	{
		if(ft_strcmp(t->attr, str) == 0)
			return (*t);
		t = t->next;
	}
	return *t;
}

t_texture get_wall_tex(t_ray ray, t_data data)
{
	t_texture *t;

	t = data.texture;
	if (ray.direction == 'h')
    {
        if (ray.ray_angle > 0 && ray.ray_angle < PI) 
            return (hh(data.texture, "SO"));
        else 
            return (hh(data.texture, "NO"));
    }
    else
	{
        if (ray.ray_angle < (PI / 2) || ray.ray_angle > 3 * (PI / 2))
            return (hh(data.texture, "EA"));
        else 
            return (hh(data.texture, "WE"));
    }
}

void draw_line_of_tex(t_data *data, double wall_height, double i)
{
	double scale_width;
	double scale_height;
	double	lim = (HEIGHT / 2) + wall_height / 2;
	double j = (HEIGHT / 2) - wall_height / 2;
	double a, b;
	unsigned int color;
	double	d;
	t_texture t = get_wall_tex(data->ray[(long long)i], *data);
	
	if (lim > HEIGHT)
		lim = HEIGHT;
	if (j < 0)
		j = 0;
    scale_height = wall_height / t.height;
    scale_width = wall_height / t.width;
	a = get_start_text(data->ray[(long long)i], t);
	while(j < lim)
	{
		b = (j - ((HEIGHT / 2) - wall_height / 2)) / scale_height;
		if(a < t.width && a >= 0 && b < t.height && b >= 0)
			color = my_mlx_pixel_get(t.img, a, b);
		if(j >= 0 && j < HEIGHT && i >= 0 && i < WIDTH)
			my_mlx_pixel_put(data, i, j, color);
		j++;
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
