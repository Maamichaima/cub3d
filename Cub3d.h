/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:24:07 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/03 00:07:59 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include "libft/libft.h"
#define SCALE 30
#define WIDTH 900
#define LENGTH 700
#define PI 3.14159265359
#define LIGNE_OF_PLAYER 20

#define W 0
#define D 1
#define S 2
#define A 3
#define R 4
#define L 5
#define ESC 6
#define P_SPEED 0.3
#define A_SPEED 0.01
#define MINIMAP_SCALE 0.25
#define FOV (60 * (PI / 180))
	

typedef struct s_player
{
	double x;
	double y;
	double dx;
	double dy;
	double angle;
} t_player;

typedef struct s_image
{
	void			*ptr_img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
} t_image;

typedef struct s_ray
{
	double 	ray_angle;
	double	wall_inter_X;
	double	wall_inter_Y;
	char 	direction;
	double	distance;
} t_ray;

typedef struct s_texture
{
	void *ptr_img;
	int   height;
	int   width;
	char *data; // path to the file
	char *attr;
	struct s_texture *next;
} t_texture;

typedef struct s_data
{
	void *mlx_ptr;
	char **map;
	void *mlx_win;
	size_t height;
	size_t width;
	char *file_map;
	int 	rayon;
	t_player player;
	t_image	 image;
	t_texture texture;
	double	num_rays;
	t_ray	*ray;
	int keys[7];
} t_data;




char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
t_texture *get_texture(int fd);
t_texture	*get_path(char *line);
int *count_length_width(char *av);
int check_map(t_data x);
int  valid_characters(char map, int *count);
void    check_characters(t_data x);
char	**get_map(int fd, t_data *x);
char	**correct_map(t_data *x);
char *skip_white_spaces(char *str);
t_texture	*ft_lstlast_txt(t_texture *lst);
void	ft_lstadd_back_txt(t_texture **lst, t_texture *new);
int	ft_strcmp(char *s1, char *s2);
int count_comma(char *ligne);
int check_is_int(char *str);
int check_color(char *ligne, char *attr);
char **fillBlanks(t_data x);
int	smya(char c);
int check_next_to_zero(char **tab, size_t i, size_t j, t_data x);
int check_zero_in_map(char **tab, t_data x);
char **alloc_map(int size);
int check_start_map(char *ligne);
int    check_textures(t_texture *txt);
void inisialise(t_data *x, char *n);
int check_all(t_data *x);
int possible_color(char *attr);
int	checkPlayer(char **map);
int is_player(char c);
int draw(t_data *x);
int key_hook(t_data *x);
void draw_line_angle(t_data *data, int x0, int y0);
void    cast_ray(t_data *x, int x0, int y0);
int  draw_ray(t_data *data, int x0, int y0, t_ray ray);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    check_vert_hitwall(t_data *data, int index, double x_inter, double y_inter, double x_step, double y_step);
void     first_V_inter( int  id_column ,t_data *data);
int is_wall(t_data x,double i ,double j);
int    check_ray_position(t_ray *ray);
double     Distance_2Points(double x,double y,double x_wall,double y_wall);
int     Ray_UP(t_ray ray);
int     Ray_DOWN(t_ray ray);
int     Ray_RIGHT(t_ray ray);
int     Ray_LEFT(t_ray ray);
void render_projected_wall(t_data *data);
void mini_map(t_data *x, double scale);
void color_one_square(int start_x, int start_y, void *x, double scale);
void    get_textures_buffer(t_data *data);
#endif