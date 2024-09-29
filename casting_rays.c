
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
double     Distance_2Points(double x,double y,double x_wall,double y_wall)
{
    return(sqrt(((x_wall - x) *(x_wall - x)) +((y_wall - y) *(y_wall - y) )));
}
void    check_ray_position(t_ray *ray)
{
    if(ray->ray_angle >= 0 && ray->ray_angle < PI)
    {
        if(ray->ray_angle >= 0 && ray->ray_angle <= PI/2)
            ray->direction = DOWN_RIGHT;
        if(ray->ray_angle >= PI/2 && ray->ray_angle <= PI)
            ray->direction = DOWN_LEFT;
    }
    else
    {
        if(ray->ray_angle >= PI && ray->ray_angle <= 3 * PI/2)
            ray->direction = UP_LEFT;
        if(ray->ray_angle > 3 * PI/2 && ray->ray_angle <= 2 * PI)
            ray->direction = UP_RIGHT;
    }
}


int  draw_ray(t_data *data, int x0, int y0 ,int x_wall, int y_wall)
{
    int x, y;
	int i;

	i = 0;
    int d = Distance_2Points(x0,y0,x_wall,y_wall);
	while (i < d)
	{
        x = x0 + i  * cos(data->ray->ray_angle);
        y = y0  + i * sin(data->ray->ray_angle);
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
    if(i < 0 || i > (x.width * SCALE) || j < 0 || j > (x.height * SCALE))
        return(0);
    a =(int) (i / SCALE);
    b = (int)(j / SCALE);
    if(x.map[b][a] == '1')
        return(1);
    return(0);
}
int    check_horz_hitwall(t_data *data, double x_inter, double y_inter, double x_step, double y_step)
{
    double next_inter_x; // pixel before the wall
    double next_inter_y;
    double is_wall_flag = 0;
    double x_wall = 0; // first intersection with the wall
    double y_wall = 0;
    double horz_distance;
    next_inter_x = x_inter;
    next_inter_y = y_inter;
    // if(data->ray->direction == UP_LEFT || data->ray->direction == UP_RIGHT)
    //     next_inter_y--;
    while(next_inter_x >= 0 && next_inter_x < (data->width * SCALE) &&  next_inter_y >= 0 &&  next_inter_y < (data->height * SCALE))
    {
        if(is_wall(*data,next_inter_x,next_inter_y))
        {   
        // puts("hh");

            is_wall_flag = 1;
            x_wall = next_inter_x ;
            y_wall = next_inter_y ;
           
            break;
        }
        else
        {   
            // printf("x=%d  y=%d\n", next_inter_x, next_inter_y );
            // my_mlx_pixel_put(data,(int)next_inter_x ,(int)  next_inter_y, 0xFFFF33);
            next_inter_x += x_step;
            next_inter_y += y_step;
        }
    }
	
    data->ray->wall_inter_X = x_wall;
    data->ray->wall_inter_Y = y_wall;
    data->ray->distance = Distance_2Points(data->player.x,data->player.y,x_wall,y_wall);
    //printf("HORIZONTAL x=%f y=%f  distance=%d \n",x_wall,y_wall, data->ray->distance);
    return(data->ray->distance);
}
int     first_H_inter( int  id_column ,t_data *data)
{
    double x_inter = 0; // first intersection with horizontal line
    double y_inter = 0;
    double x_step = 0 ; // the delta distance between one intersection to an other
    double y_step = 0;
    

    y_inter =(int)(data->player.y / SCALE) * SCALE ;
	if(data->ray->direction == UP_RIGHT || data->ray->direction == UP_LEFT)
       y_inter  += (SCALE);
    x_inter =  data->player.x + ( (y_inter - data->player.y)  / tan(data->ray->ray_angle));
    y_step = SCALE;
    x_step = (int)(SCALE / tan(data->ray->ray_angle));
    if(data->ray->direction == UP_LEFT || data->ray->direction == UP_RIGHT)
    {
        y_step *= -1;
        x_step *= -1;
    }
    return(check_horz_hitwall(data, x_inter, y_inter, x_step, y_step));
}

void    cast_ray(t_data *x, int x0, int y0) 
{
    int num_rays =(x->width * SCALE) / 10;
    int id_column = 0;
    int i = 0;
    int min;

    double ray_angle;

    ray_angle = x->player.angle ;//- (FOV / 2);// protect_angle
    x->ray->ray_angle = protect_angle(&ray_angle);
    first_H_inter(id_column,x);
    first_V_inter(id_column,x);
	draw_ray(x, x->player.x, x->player.y, x->ray->wall_inter_X,x->ray->wall_inter_Y);
    //my_mlx_pixel_put(x,(int)x->ray->wall_inter_X ,(int)x->ray->wall_inter_Y, 0xFF0000);
    // ray_angle = x->ray.ray_angle + FOV / num_rays;
    // x->ray.ray_angle = protect_angle(&ray_angle);
    
    //printf("x=%d y=%d x_wal=%d y_wall=%d\n",(int)x->player.x,(int) x->player.y,(int) x->ray->wall_inter_X,(int)x->ray->wall_inter_Y);
    // if( first_H_inter(id_column,x) < first_V_inter(id_column,x))
    //     min = first_H_inter(id_column,x);
    // else
    //     min = first_V_inter(id_column,x);

    //printf("Y=%d  X=%d  min=%d\n",data->ray->wall_inter_X, data->ray->wall_inter_X,min);
    // while(i < num_rays)
    // {
    //     ray_angle = x->ray->ray_angle + FOV / num_rays;
    //     x->ray->ray_angle = protect_angle(&ray_angle);
	// 	first_H_inter(id_column,x);
	// 	first_V_inter(id_column,x);
	// 	draw_ray(x, x->player.x, x->player.y, x->ray->wall_inter_X,x->ray->wall_inter_Y);
    //    // draw_line_angle(x, x0,y0);
        
    //     id_column++;
    //     i++;
    // }
    
    
    // protect angle 
    
}