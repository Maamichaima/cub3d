
#include "Cub3d.h"

double protect_angle(double *angle)
{
    while (*angle >= 2 * PI)
    {
        *angle -= 2 * PI;
    }
    while (*angle < 0)
    {
        *angle += 2 * PI;
    }
    return(*angle);
}
// int     Distance_2Points(int x,int y,int x_wall,int y_wall)
// {
//     return(sqrt(((x_wall - x) *(x_wall - x)) +((y_wall - y) *(y_wall - y) )));
// }
void    check_ray_position(t_ray *ray)
{
    if(ray->ray_angle >= 0 && ray->ray_angle < PI)
        ray->direction = DOWN;
    else if(!(ray->ray_angle >= 0 && ray->ray_angle < PI))
         ray->direction = UP;
    else if(ray->ray_angle < 0.5 * PI  || ray->ray_angle > 1.5 * PI)
        ray->direction = RIGHT;
    else if(!(ray->ray_angle < 0.5 * PI  || ray->ray_angle > 1.5 * PI))
        ray->direction = LEFT;
}


int  draw_ray(t_data *data, int x0, int y0 ,int x_wall, int y_wall)
{
    int x, y;
	int i;

	i = 0;

	while (i < LIGNE_OF_PLAYER)//(x >= 0 && y >=0 && x < data->height && y < data->width) && data->map[x][y] == '0')
	{
        x = x0 + i * cos(data->ray.ray_angle);
        y = y0 + i * sin(data->ray.ray_angle);
		if(x >= 0 && y >= 0)
			my_mlx_pixel_put(data, x, y, 0xFFFF33);
		i++;
	}
    return(0);
}
int is_wall(t_data x,int i ,int j)
{
    int a;
    int b;

    a = i / SCALE;
    b = j / SCALE;

    if(a >= 0 && a < x.height && b >= 0 && b < x.width && x.map[(int)a][(int)b] == '1')
        return(1);
    return(0);
}
// int    check_horz_hitwall(t_data *data, int x_inter, int y_inter, int x_step, int y_step)
// {
//     int next_inter_x; // pixel before the wall
//     int next_inter_y;
//     int is_wall_flag = 0;
//     int x_wall = 0; // first intersection with the wall
//     int y_wall = 0;
//     int horz_distance;

//     next_inter_x = x_inter;
//     next_inter_y = y_inter;
//     if(data->ray.direction == UP)
//         next_inter_y--;
//     while(next_inter_x >= 0 && next_inter_x < (data->width * SCALE) &&  next_inter_y >= 0 &&  next_inter_y < (data->height * SCALE))
//     {
//         if(is_wall(*data,next_inter_x,next_inter_y))
//         {   
//         // puts("hh");
//             is_wall_flag = 1;
//             x_wall = next_inter_x ;
//             y_wall = next_inter_y ;

//             break;
//         }
//         else
//         {   
//             // printf("x=%d  y=%d\n", next_inter_x, next_inter_y );
           
//             next_inter_x += x_step;
//             next_inter_y += y_step;
//         }
 
//     }
//     horz_distance = Distance_2Points(data->player.x,data->player.y,x_wall,y_wall);
//     return(horz_distance);
// }
void     first_H_inter( int  id_column ,t_data *data)
{
    double x_inter = 0; // first intersection with horizontal line
    double y_inter = 0;
    double x_step = 0 ; // the delta distance between one intersection to an other
    double y_step = 0;
    

    y_inter =(int)(data->player.y / SCALE) * SCALE ;
    x_inter =  data->player.x + ( (y_inter - data->player.y)  / tan(data->ray.ray_angle));
    if(data->ray.direction == DOWN)
        y_inter  += SCALE;
    y_step = SCALE;
    x_step = (int)(SCALE / tan(data->ray.ray_angle));
    // if(data->ray.direction == UP )
    //     y_step  *= -1;
    // if(data->ray.direction == LEFT && x_step > 0)
    //     x_step  *= -1;
    // else if(data->ray.direction == RIGHT && x_step < 0)
    //     x_step  *= -1;
     //printf("%d  %d\n",  ((int) y_step + (int) y_inter), ( (int)x_step + (int) x_inter ));
    if( (x_inter + x_step) >= 0 && ( y_inter + y_step) >= 0 && (x_inter + x_step) < (data->width * SCALE) &&( y_inter + y_step) < (data->height * SCALE))
    {    
        printf("%d  %d\n",  ((int) y_inter + (int) y_step), ((int) x_inter + (int)x_step));
        my_mlx_pixel_put(data, ((int) x_inter + (int)x_step), ((int) y_inter +  (int) y_step) ,0xFFFF33);
    }
    // check_horz_hitwall(data,x_inter,y_inter,x_step,y_step);
    
}

void    cast_ray(t_data *x, int x0, int y0) 
{
    int num_rays =(x->width * SCALE) / 1;
    int id_column = 0;
    int i = 0;

    double ray_angle;

    ray_angle = x->player.angle; //- (FOV / 2);// protect_angle
    x->ray.ray_angle = protect_angle(&ray_angle);
    // ray_angle = x->ray.ray_angle + FOV / num_rays;
    // x->ray.ray_angle = protect_angle(&ray_angle);
    first_H_inter(id_column,x);
    // while(i < 1)
    // {
    //     ray_angle = x->ray.ray_angle + FOV / num_rays;
    //     x->ray.ray_angle = protect_angle(&ray_angle);
    //     first_H_inter(id_column,x); 
        
    //    // draw_line_angle(x, x0,y0);
        
    //     id_column++;
    //     i++;
    // }
    
    
    // protect angle 
    
}