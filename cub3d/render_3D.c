/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:34:11 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 15:20:31 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	draw_line_of_tex(t_data *data, double wall_height, double i)
{
	unsigned int	color;
	t_texture		t;
	t_coordinate	index;

	double (scale_height), (lim), (a), (b);
	set_value(&index, i, (HEIGHT / 2) - wall_height / 2);
	lim = (HEIGHT / 2) + wall_height / 2;
	t = get_wall_tex(data->ray[(long long)index.x], *data);
	if (lim > HEIGHT)
		lim = HEIGHT;
	if (index.y < 0)
		index.y = 0;
	scale_height = wall_height / t.height;
	a = get_start_text(data->ray[(long long)index.x], t);
	while (index.y < lim)
	{
		b = (index.y - ((HEIGHT / 2) - wall_height / 2)) / scale_height;
		if (a < t.width && a >= 0 && b < t.height && b >= 0)
			color = my_mlx_pixel_get(t.img, a, b);
		if (index.y >= 0 && index.y < HEIGHT && index.x >= 0 && index.x < WIDTH)
			my_mlx_pixel_put(data, index.x, index.y, color);
		index.y++;
	}
}

void	draw_flor_ceiling(t_data *data)
{
	double	max_distance;
	double	d;
	double	factor;

	double (i), (j);
	i = 0;
	j = 0;
	max_distance = HEIGHT / 2;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			d = distance_from_center(j);
			factor = 1 - (d / max_distance);
			if (j < HEIGHT / 2)
				my_mlx_pixel_put(data, i, j, data->c);
			else if (j > HEIGHT / 2)
				my_mlx_pixel_put(data, i, j, data->f);
			j++;
		}
		i++;
	}
}

void	render_projected_wall(t_data *data)
{
	int		j;
	int		color;
	double	correct_wall_distance;
	double	max_distance;

	double (i), (d_projection_plane), (wall_height);
	i = 0;
	j = 0;
	color = 0;
	max_distance = HEIGHT / 2;
	draw_flor_ceiling(data);
	i = 0;
	while (i < data->num_rays)
	{
		d_projection_plane = (WIDTH / 2) / tan(FOV / 2);
		correct_wall_distance = data->ray[(long long)i].distance
			* cos(data->ray[(long long)i].ray_angle - data->player.angle);
		wall_height = (SCALE / correct_wall_distance) * d_projection_plane;
		draw_line_of_tex(data, wall_height, i);
		i++;
	}
}
