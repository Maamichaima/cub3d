/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:30:25 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/30 18:17:14 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double protect_angle(double angle)
{
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    while (angle < 0)
        angle += 2 * PI;
    return(angle);
}
double     Distance_2Points(double x,double y,double x_wall,double y_wall)
{
    return(sqrt(((x_wall - x) * (x_wall - x)) + ((y_wall - y) * (y_wall - y) )));
}
// int    check_ray_position(t_ray *ray)
// {
//     if(ray->ray_angle >= 0 && ray->ray_angle < PI)
//             ray->direction = DOWN; 
    
//     if(ray->ray_angle >= (1.5 * PI) && ray->ray_angle < (0.5 * PI))
//             ray->direction = RIGHT;
//     if(!(ray->ray_angle >= (1.5 * PI) && ray->ray_angle < (0.5 * PI)))
//             ray->direction = LEFT;
// 	return(ray->direction);
// }
int     Ray_UP(t_ray ray)
{
    if(ray.ray_angle >= PI && ray.ray_angle < 2 * PI)
        return(1);
    return(0);
}
int     Ray_DOWN(t_ray ray)
{
    if(ray.ray_angle >= 0 && ray.ray_angle < PI)
        return(1);
    return(0);
}
int     Ray_RIGHT(t_ray ray)
{
    if(ray.ray_angle <= ( PI / 2) || ray.ray_angle > (3 * PI/2))
        return(1);
    return(0);
}
int     Ray_LEFT(t_ray ray)
{
    if(ray.ray_angle > ( PI / 2) && ray.ray_angle <= ( 3 * PI/2))
        return(1);
    return(0);
}

int  draw_ray(t_data *data, int x0, int y0 , t_ray ray)//,int x_wall, int y_wall)
{
    int x, y;
	int i;

	i = 0;
    int d = Distance_2Points(x0, y0, ray.wall_inter_X, ray.wall_inter_Y);
	while (i < d)
	{
        x = x0 + i  * cos(ray.ray_angle);
        y = y0  + i * sin(ray.ray_angle);
		if(x >= 0 && y >= 0)
			my_mlx_pixel_put(data, x, y, 0xFFFF33);
		i++;
	}
    return(0);
}

int is_wall(t_data x,double i ,double j)
{
    int a;
    int b;
    if(i < 0 || i > (x.width * SCALE) || j < 0 || j > (x.height * SCALE))
        return(0);
    a =(int) (i / SCALE);
    b = (int)(j / SCALE);
    if(x.map[b][a] == '1')
        return(1);
    return(0);
}
void    check_horz_hitwall(t_data *data, int index, double x_inter, double y_inter, double x_step, double y_step)
{
    double next_inter_x; // pixel before the wall
    double next_inter_y;
    double x_wall = 0; // first intersection with the wall
    double y_wall = 0;
    next_inter_x = x_inter;
    next_inter_y = y_inter;
   
    if(Ray_UP(data->ray[index]))
        next_inter_y--;
    while(next_inter_x >= 0 && next_inter_x < (data->width * SCALE) &&  next_inter_y >= 0 &&  next_inter_y < (data->height * SCALE))
    {
        if(is_wall(*data,next_inter_x,next_inter_y))
        {
            x_wall = next_inter_x ;
            y_wall = next_inter_y ;
            break;
        }
        else
        {
            next_inter_x += x_step;
            next_inter_y += y_step;
        }
    }
    data->ray[index].wall_inter_X = x_wall;
    data->ray[index].wall_inter_Y = y_wall;
    data->ray[index].distance = Distance_2Points(data->player.x, data->player.y, x_wall, y_wall);
}
void     first_H_inter(int index ,t_data *data)
{
    double x_inter = 0; // first intersection with horizontal line
    double y_inter = 0;
    double x_step = 0 ; // the delta distance between one intersection to an other
    double y_step = 0;

    y_inter =(int)(data->player.y / SCALE) * SCALE ;
	if(Ray_DOWN(data->ray[index]))
       y_inter  += (SCALE);
    x_inter =  data->player.x + (y_inter - data->player.y)  / tan(data->ray[index].ray_angle);
    y_step = SCALE;
    if(Ray_UP(data->ray[index]))
        y_step *= -1;
    x_step =(int) SCALE / tan(data->ray[index].ray_angle);
    if(Ray_RIGHT(data->ray[index])&& x_step < 0)
        x_step *=-1;
    if(Ray_LEFT(data->ray[index]) && x_step > 0)
        x_step *=-1;
    check_horz_hitwall(data, index, x_inter, y_inter, x_step, y_step);
}

void    cast_ray(t_data *x, int x0, int y0) 
{
    int id_column = 0;
    int i = 0;
    double ray_angle;
	double d_V;
	double d_H;

    ray_angle = x->player.angle - (FOV / 2);// protect_angle
    x->ray[i].ray_angle = protect_angle(ray_angle);
    while(i < x->num_rays)
    {
		if(i != 0)
		{
        	x->ray[i].ray_angle = x->ray[i - 1].ray_angle + FOV / x->num_rays;
        	x->ray[i].ray_angle = protect_angle(x->ray[i].ray_angle);
		}
		first_H_inter(i, x);
		first_V_inter(i, x);
		// draw_ray(x, x->player.x, x->player.y, x->ray[i]);
    	// draw_line_angle(x, x0,y0);
    //     id_column++;
        i++;
    }
	rander_prijected_wall(x);
}

