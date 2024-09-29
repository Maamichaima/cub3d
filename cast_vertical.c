/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:44:38 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/29 11:02:17 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int    check_vert_hitwall(t_data *data, double x_inter, double y_inter, double x_step, double y_step)
{
    double next_inter_x; // pixel before the wall
    double next_inter_y;
    double is_wall_flag = 0;
    double x_wall = 0; // first intersection with the wall
    double y_wall = 0;
    double vert_distance;

    next_inter_x = x_inter;
    next_inter_y = y_inter;
    // if(data->ray->direction == UP_LEFT || data->ray->direction == DOWN_LEFT)
    //     next_inter_x--;
    while(next_inter_x >= 0 && next_inter_x < (data->width * SCALE) &&  next_inter_y >= 0 &&  next_inter_y < (data->height * SCALE))
    {
        if(is_wall(*data,next_inter_x,next_inter_y))
        {   
            is_wall_flag = 1;
            x_wall = next_inter_x ;
            y_wall = next_inter_y ;
            break;
        }
        else
        {   
            // my_mlx_pixel_put(data,(int)next_inter_x ,(int)  next_inter_y, 0xFFFF33);
            next_inter_x += x_step ;
            next_inter_y += y_step ;
        }
    }
    vert_distance = Distance_2Points(data->player.x,data->player.y,x_wall,y_wall);
    if( vert_distance < data->ray->distance)
    {   
        data->ray->distance = vert_distance;
        data->ray->wall_inter_X = x_wall;
        data->ray->wall_inter_Y = y_wall;
    }
     //printf("VERTICAL x=%f y=%f  distance=%d \n",x_wall,y_wall, data->ray->distance);
    return(vert_distance);
}

int    first_V_inter( int  id_column ,t_data *data)
{
    double x_inter = 0; // first intersection with horizontal line
    double y_inter = 0;
    double x_step = 0 ; // the delta distance between one intersection to an other
    double y_step = 0;
    
    x_inter =(int)(data->player.x / SCALE  ) * SCALE ;
    if(data->ray->direction == UP_RIGHT || data->ray->direction == DOWN_RIGHT)
       x_inter  += (SCALE);// - data->player.x);
    y_inter =  data->player.y + ( (x_inter - data->player.x) * tan(data->ray->ray_angle));
    x_step = SCALE;
    y_step =(int) (SCALE * tan(data->ray->ray_angle));
    if (data->ray->direction == UP_LEFT || data->ray->direction == DOWN_LEFT)
    {
        x_step *= -1;
        y_step *= -1;
    }
	// printf("inter --> %f x_player--> %f\n", x_inter, data->player.x);
    return(check_vert_hitwall(data, x_inter, y_inter, x_step, y_step));
}

 // if(data->ray.direction == UP_RIGHT || data->ray.direction == DOWN_RIGHT)
    //     x_inter  -= SCALE;
// if(data->ray.direction == UP_LEFT || data->ray.direction == DOWN_LEFT )
    //     x_step  *= -1;
    // if((data->ray.direction == UP_LEFT || data->ray.direction == UP_RIGHT) && y_step > 0)
    //     y_step  *= -1;
    // else if((data->ray.direction == DOWN_LEFT || data->ray.direction == DOWN_RIGHT) && y_step < 0)
    //     y_step  *= -1;
     //my_mlx_pixel_put(data, ((int) x_inter - (int)x_step), ((int) y_inter -  (int) y_step) ,0xFFFF33);