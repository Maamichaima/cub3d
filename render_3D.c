/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:34:11 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/18 18:22:29 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double dmod(double x, double y)
{
    return x - (long long)(x/y) * y;
}

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
	if(ray.is_door)
		return(hh(data.texture,"d"));
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

unsigned int Darkness(unsigned int color, double distance, int max_distance)
{
    int r, g, b;
    double dark_factor;

    // double max_distance = 500;
    dark_factor = 1 - (distance / max_distance); 
    if (dark_factor < 0)
        dark_factor = 0;
    if (dark_factor > 1)
        dark_factor = 1;
    r = (color >> 16) & 0xFF;//0xFF == 00000000000000000000000011111111
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;	
    r = r * dark_factor;
    g = g * dark_factor;
    b = b * dark_factor;
    return (r << 16) | (g << 8) | b;
}

void draw_line_of_tex(t_data *data, double wall_height, double i)
{
	double scale_height;
	double	lim = (HEIGHT / 2) + wall_height / 2;
	double j = (HEIGHT / 2) - wall_height / 2;
	double a, b;
	unsigned int color;
	t_texture t = get_wall_tex(data->ray[(long long)i], *data);
	
	if (lim > HEIGHT)
		lim = HEIGHT;
	if (j < 0)
		j = 0;
    scale_height = wall_height / t.height;
	a = get_start_text(data->ray[(long long)i], t);
	while(j < lim)
	{
		b = (j - ((HEIGHT / 2) - wall_height / 2)) / scale_height;
		if(a < t.width && a >= 0 && b < t.height && b >= 0)
		{
			color = my_mlx_pixel_get(t.img, a, b);
			color = Darkness(color, data->ray[(long long)i].distance, HEIGHT);
		}
		if(j >= 0 && j < HEIGHT && i >= 0 && i < WIDTH)
			my_mlx_pixel_put(data, i, j, color);
		j++;
	}
}

unsigned int apply_darkness(unsigned int color, double dark_factor)
{
    unsigned char r, g, b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    r = (unsigned char)(r * (1 - dark_factor));
    g = (unsigned char)(g * (1 - dark_factor));
    b = (unsigned char)(b * (1 - dark_factor));
    return (r << 16) | (g << 8) | b;
}

void draw_flor_ceiling(t_data *data)
{
	double i = 0;
	double j = 0;
    double max_distance = HEIGHT / 2;
	unsigned int color;
	
	
	while(i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            
            double distance_from_center = (j < HEIGHT / 2) ? (HEIGHT / 2 - j) : (j - HEIGHT / 2);
            double dark_factor = 1 - (distance_from_center / max_distance);
            if (dark_factor < 0)
				dark_factor = 0;  
            if (dark_factor > 1)
				dark_factor = 1;
            if (j < HEIGHT / 2)
                my_mlx_pixel_put(data, i, j, apply_darkness(0x34baeb, dark_factor));
            else if (j > HEIGHT / 2)
                my_mlx_pixel_put(data, i, j, apply_darkness(0xeb6b34, dark_factor));
            j++;
        }
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
    double max_distance = HEIGHT / 2;

	draw_flor_ceiling(data);
    i = 0;
    while(i < data->num_rays)
    {
        d_projection_plane = (WIDTH / 2) / tan(FOV / 2); 
        correct_wall_distance = data->ray[(long long)i].distance * cos(data->ray[(long long)i].ray_angle - data->player.angle);
        wall_height = (SCALE / correct_wall_distance) * d_projection_plane;
        draw_line_of_tex(data, wall_height, i);
        i++;
    }
}


