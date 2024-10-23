/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:30:25 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/23 19:02:58 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double	protect_angle(double angle)
{
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	while (angle < 0)
		angle += 2 * PI;
	return (angle);
}
double	Distance_2Points(double x, double y, double x_wall, double y_wall)
{
	if (x_wall == 0 && y_wall == 0)
		return (INT_MAX);
	return (sqrt(((x_wall - x) * (x_wall - x)) + ((y_wall - y) * (y_wall
					- y))));
}

int	Ray_UP(t_ray ray)
{
	if (ray.ray_angle >= PI && ray.ray_angle < 2 * PI)
		return (1);
	return (0);
}

int	Ray_DOWN(t_ray ray)
{
	if (ray.ray_angle >= 0 && ray.ray_angle < PI)
		return (1);
	return (0);
}

int	Ray_RIGHT(t_ray ray)
{
	if (ray.ray_angle <= (PI / 2) || ray.ray_angle > (3 * PI / 2))
		return (1);
	return (0);
}

int	Ray_LEFT(t_ray ray)
{
	if (ray.ray_angle > (PI / 2) && ray.ray_angle <= (3 * PI / 2))
		return (1);
	return (0);
}

int	draw_ray(t_data *data, int x0, int y0, t_ray ray) //,int x_wall, int y_wall)
{
	int	i;
	int	d;

	int x, y;
	i = 0;
	d = Distance_2Points(x0, y0, ray.wall_inter_x, ray.wall_inter_y);
	while (i < d)
	{
		x = x0 + i * cos(ray.ray_angle);
		y = y0 + i * sin(ray.ray_angle);
		if (x >= 0 && y >= 0)
			my_mlx_pixel_put(data, x * MINIMAP_SCALE, y * MINIMAP_SCALE,
				0xFFFF33);
		i++;
	}
	return (0);
}

int	is_wall(t_data x, double i, double j)
{
	int	a;
	int	b;

	if (i < 0 || i > (x.width * SCALE) || j < 0 || j > (x.height * SCALE))
		return (0);
	a = (int)(i / SCALE);
	b = (int)(j / SCALE);
	if (x.map[b][a] == '1')
	{
		return (1);
	}
	return (0);
}
int	hit_door(t_data *x, int index, double i, double j)
{
	int	a;
	int	b;

	if (i < 0 || i > (x->width * SCALE) || j < 0 || j > (x->height * SCALE))
		return (0);
	a = (int)(i / SCALE);
	b = (int)(j / SCALE);
	if (x->map[b][a] == 'd')
	{
		// x->ray[index].is_door = 1;
		return (1);
	}
	return (0);
}

int	hit_o(t_data x, double i, double j)
{
	int	a;
	int	b;

	if (i < 0 || i > (x.width * SCALE) || j < 0 || j > (x.height * SCALE))
		return (0);
	a = (int)(i / SCALE);
	b = (int)(j / SCALE);
	if (x.map[b][a] == 'O')
		return (1);
	return (0);
}

void	check_horz_hitwall(t_data *data, int index, t_coordinate inter,
		t_coordinate step)
{
	double	next_inter_x;
	double	next_inter_y;
	double	y_wall;
	int		is_door;
	int		is_open_door;
	t_ray	ray;

	double x_wall = 0; // first intersection with the wall
	y_wall = 0;
	next_inter_x = inter.x;
	next_inter_y = inter.y;
	is_door = 0;
	is_open_door = 0;
	data->ray[index].is_open = 0;
	if (Ray_UP(data->ray[index]))
		next_inter_y -= 0.00001;
	while (next_inter_x >= 0 && next_inter_x < (data->width * SCALE)
		&& next_inter_y >= 0 && next_inter_y < (data->height * SCALE))
	{
		if (!is_open_door && hit_o(*data, next_inter_x, next_inter_y))
		{
			data->ray[index].x = next_inter_x;
			data->ray[index].y = next_inter_y;
			is_open_door = 1;
		}
		if (is_wall(*data, next_inter_x, next_inter_y))
		{
			x_wall = next_inter_x;
			y_wall = next_inter_y;
			break ;
		}
		else if (hit_door(data, index, next_inter_x, next_inter_y))
		{
			x_wall = next_inter_x;
			y_wall = next_inter_y;
			is_door = 1;
			break ;
		}
		next_inter_x += step.x;
		next_inter_y += step.y;
	}
	data->ray[index].wall_inter_x = x_wall;
	data->ray[index].wall_inter_y = y_wall;
	data->ray[index].distance = Distance_2Points(data->player.x, data->player.y,
			x_wall, y_wall);
	data->ray[index].direction = 'h';
	data->ray[index].is_door = is_door;
	data->ray[index].is_open = is_open_door;
	// if(ray.wall_inter_X  &&  ray.wall_inter_Y)
	//     implement_door_status(data,ray);
}

void	first_H_inter(int index, t_data *data)
{
	t_coordinate inter;
	t_coordinate step;
	
	inter.x = 0;
	inter.y = 0;
	step.x = 0;
	step.y = 0;
	inter.y = (int)floor(data->player.y / SCALE) * SCALE;
	if (Ray_DOWN(data->ray[index]))
		inter.y += (SCALE);
	inter.x = data->player.x + (inter.y - data->player.y)
		/ tan(data->ray[index].ray_angle);
	step.y = SCALE;
	if (Ray_UP(data->ray[index]))
		step.y *= -1;
	step.x = SCALE / tan(data->ray[index].ray_angle);
	if (Ray_RIGHT(data->ray[index]) && step.x < 0)
		step.x *= -1;
	if (Ray_LEFT(data->ray[index]) && step.x > 0)
		step.x *= -1;
	check_horz_hitwall(data, index, inter, step);
}
void	door_keys(t_data *x)
{
	int	i;
	int	flag;
	int	flag1;

	// test
	i = 0;
	double current_distance, closet_distance = INT_MAX;
	double distance, open_distance = INT_MAX;
	flag = -1;
	flag1 = -1;
	while (i < x->num_rays)
	{
		if (x->ray[i].is_door)
		{
			current_distance = x->ray[i].distance;
			// Distance_2Points(x->player.x,x->player.y,x->ray[i].wall_inter_X,x->ray[i].wall_inter_Y);
			if (current_distance < closet_distance)
			{
				closet_distance = current_distance;
				flag = i;
			}
		}
		else if (x->ray[i].is_open)
		{
			distance = Distance_2Points(x->player.x, x->player.y, x->ray[i].x,
					x->ray[i].y);
			if (distance < open_distance)
			{
				open_distance = distance;
				flag1 = i;
			}
		}
		i++;
	}
	// printf("%f\n",closet_distance);
	if (x->keys[O] && flag != -1 && closet_distance < 250)
		x->map[(int)x->ray[flag].wall_inter_y
			/ SCALE][(int)x->ray[flag].wall_inter_x / SCALE] = 'O';
	if (x->keys[C] && flag1 != -1 && open_distance < 250)
		x->map[(int)x->ray[flag1].y / SCALE][(int)x->ray[flag1].x
			/ SCALE] = 'd';
	x->keys[C] = 0;
	x->keys[O] = 0;
}

void	cast_ray(t_data *x, int x0, int y0)
{
	int		id_column;
	int		i;
	double	ray_angle;
	double	d_V;
	double	d_H;

	id_column = 0;
	i = 0;
	ray_angle = x->player.angle - (FOV / 2); // protect_angle
	x->ray[i].ray_angle = protect_angle(ray_angle);
	while (i < x->num_rays)
	{
		if (i != 0)
		{
			x->ray[i].ray_angle = x->ray[i - 1].ray_angle + FOV / x->num_rays;
			x->ray[i].ray_angle = protect_angle(x->ray[i].ray_angle);
		}
		first_H_inter(i, x);
		first_V_inter(i, x);
		i++;
	}
	door_keys(x);
	// test
}
