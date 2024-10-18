/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:44:38 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/02 21:58:49 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void    check_vert_hitwall(t_data *data, int index, double x_inter, double y_inter, double x_step, double y_step)
{
    double next_inter_x; // pixel before the wall
    double next_inter_y;
    double is_wall_flag = 0;
    double x_wall = 0; // first intersection with the wall
    double y_wall = 0;
    double vert_distance = 0;
    int is_door = 0;

    next_inter_x = x_inter;
    next_inter_y = y_inter;
    if(Ray_LEFT(data->ray[index]))
        next_inter_x -= 0.00001;
    while(next_inter_x >= 0 && next_inter_x < (data->width * SCALE) &&  next_inter_y >= 0 &&  next_inter_y < (data->height * SCALE))
    {
		// printf("x = %f | y = %f\n", next_inter_x, next_inter_y);
        if(is_wall(*data,next_inter_x,next_inter_y) )
        {
            x_wall = next_inter_x ;
            y_wall = next_inter_y ;
            break;
           
        }
        else if (hit_door(data,next_inter_x,next_inter_y))
        {
            x_wall = next_inter_x ;
            y_wall = next_inter_y ;
            is_door = 1;
            break;
        }
         next_inter_x += x_step;
         next_inter_y += y_step;
    }
    vert_distance = Distance_2Points(data->player.x, data->player.y, x_wall, y_wall);
    if(vert_distance < data->ray[index].distance)
    {
        data->ray[index].distance = vert_distance;
		data->ray[index].wall_inter_X = x_wall;
		data->ray[index].wall_inter_Y = y_wall;
		data->ray[index].direction = 'v';
        data->ray[index].is_door = is_door;
    }
}

void    first_V_inter(int index ,t_data *data)
{
    double x_inter = 0; // first intersection with horizontal line
    double y_inter = 0;
    double x_step = 0 ; // the delta distance between one intersection to an other
    double y_step = 0;
    
    x_inter =(int) floor(data->player.x / SCALE ) * SCALE ;
    if(Ray_RIGHT(data->ray[index]) )
       x_inter  += (SCALE);
    y_inter =  data->player.y + ( (x_inter - data->player.x) * tan(data->ray[index].ray_angle));
    x_step = SCALE;
    if(Ray_LEFT(data->ray[index]))
        x_step *= -1;
    y_step = (SCALE * tan(data->ray[index].ray_angle));
    if(Ray_UP(data->ray[index]) && y_step > 0)
        y_step *= -1;
    if(Ray_DOWN(data->ray[index]) && y_step < 0)
        y_step *= -1;
    check_vert_hitwall(data, index, x_inter, y_inter, x_step, y_step);
}