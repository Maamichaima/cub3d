#include "Cub3d.h"

int    check_vert_hitwall(t_data *data, int x_inter, int y_inter, int x_step, int y_step)
{
    // int next_inter_x; // pixel before the wall
    // int next_inter_y;
    // int is_wall_flag = 0;
    // int x_wall = 0; // first intersection with the wall
    // int y_wall = 0;
    // int vert_distance;

    // next_inter_x = x_inter;
    // next_inter_y = y_inter;
    // if(data->ray.direction == LEFT)
    //     next_inter_x--;
    // while(next_inter_x >= 0 && next_inter_x < (data->width * SCALE) &&  next_inter_y >= 0 &&  next_inter_y < (data->height * SCALE))
    // {
    //     if(is_wall(*data,next_inter_x,next_inter_y))
    //     {   
    //         is_wall_flag = 1;
    //         x_wall = next_inter_x / SCALE;
    //         y_wall = next_inter_y / SCALE;
    //         break;
    //     }
    //     else
    //     {   
    //         next_inter_x += x_step;
    //         next_inter_y += y_step;
    //     }
 
    // }
   // vert_distance = Distance_2Points(data->player.x,data->player.y,x_wall,y_wall);
    //return(vert_distance);
    return(0);

}

void     first_V_inter( int  id_column ,t_data *data)
{
    int x_inter; // first intersection with horizontal line
    int y_inter;
    int x_step; // the delta distance between one intersection to an other
    int y_step;
    

    x_inter =( data->player.x / SCALE  ) * SCALE ;
    y_inter =  data->player.y + ( (x_inter - data->player.x)  * tan(data->ray.ray_angle));
    if(data->ray.direction == RIGHT)
        x_inter  += SCALE;
    x_step = SCALE;
    y_step = SCALE / tan(data->ray.ray_angle);
    if(data->ray.direction == LEFT )
        x_step  *= -1;
    if(data->ray.direction == UP && y_step > 0)
        y_step  *= -1;
    else if(data->ray.direction == DOWN && y_step < 0)
        y_step  *= -1;
    
    check_vert_hitwall(data,x_inter,y_inter,x_step,y_step);
}