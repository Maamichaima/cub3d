/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:24:07 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 00:41:10 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include <mlx.h> // linux
# include "mlx/mlx.h" // mac
// # include <X11/X.h>
// # include <X11/keysym.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# define SCALE 100
# define WIDTH 1280
# define HEIGHT 720
# define PI 3.14159265359
# define LIGNE_OF_PLAYER 20

# define W 0
# define D 1
# define S 2
# define A 3
# define R 4
# define L 5
# define ESC 6
# define O 7
# define C 8
# define P_SPEED 4
# define P_DISTANCE 15
# define A_SPEED 0.05
# define MINIMAP_SCALE 15
# define FOV 1.0471975512

typedef struct s_player
{
	double				x;
	double				y;
	double				dx;
	double				dy;
	double				angle;
}						t_player;

typedef struct s_image
{
	void				*ptr_img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

typedef struct s_coordinate
{
	double				x;
	double				y;
}						t_coordinate;

typedef struct s_ray
{
	double				ray_angle;
	double				wall_inter_x;
	double				wall_inter_y;
	char				direction;
	double				distance;
	int					is_door;
	int					is_open;
	int					x;
	int					y;
}						t_ray;

typedef struct s_texture
{
	t_image				img;
	void				*ptr_img;
	int					height;
	int					width;
	char				*data;
	char				*attr;
	struct s_texture	*next;
}						t_texture;

typedef struct s_data
{
	void				*mlx_ptr;
	char				**map;
	void				*mlx_win;
	size_t				height;
	size_t				width;
	char				*file_map;
	int					rayon;
	t_player			player;
	t_image				image;
	t_texture			*texture;
	double				num_rays;
	t_ray				*ray;
	int					keys[9];
	t_texture			animation[91];
	int					ff;
	unsigned int		c;
	unsigned int		f;
}						t_data;

typedef struct s_garbage
{
	void				*p;
	struct s_garbage	*next;
}						t_garbage;


char					*get_next_line(int fd);
size_t					ft_strlen(const char *s);
t_texture				*get_texture(int fd);
t_texture				*get_path(char *line);
int						*count_length_width(char *av);
int						check_map(t_data x);
int						valid_characters(char map, int *count);
void					check_characters(t_data x);
char					**get_map(int fd, t_data *x);
char					**correct_map(t_data *x);
char					*skip_white_spaces(char *str);
t_texture				*ft_lstlast_txt(t_texture *lst);
void					ft_lstadd_back_txt(t_texture **lst, t_texture *new);
int						ft_strcmp(char *s1, char *s2);
int						count_comma(char *ligne);
int						check_is_int(char *str);
int						check_color(char *ligne, char *att, t_data *x);
char					**fillBlanks(t_data x);
int						smya(char c);
int						check_next_to_zero(char **tab, size_t i, size_t j,
							t_data x);
int						check_zero_in_map(char **tab, t_data x);
char					**alloc_map(int size);
int						check_start_map(char *ligne);

void					inisialise(t_data *x, char *n);
int						check_all(t_data *x);
int						possible_color(char *attr);
int						checkPlayer(char **map);
int						is_player(char c);
int						draw(t_data *x);
int						key_hook(t_data *x);
void					draw_line_angle(t_data *data, int x0, int y0);
void					cast_ray(t_data *x, int x0, int y0);
int						draw_ray(t_data *data, int x0, int y0, t_ray ray);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
void					check_vert_hitwall(t_data *data, int index,
							t_coordinate inter, t_coordinate step);
void					first_V_inter(int id_column, t_data *data);
int						is_wall(t_data x, double i, double j);
double					Distance_2Points(double x, double y, double x_wall,
							double y_wall);
int						Ray_UP(t_ray ray);
int						Ray_DOWN(t_ray ray);
int						Ray_RIGHT(t_ray ray);
int						Ray_LEFT(t_ray ray);
void					render_projected_wall(t_data *data);
void					mini_map(t_data *x);
void					color_one_square(int start_x, int start_y, void *x,
							double scale);
void					get_textures_buffer(t_data *data);
unsigned int			my_mlx_pixel_get(t_image image, int x, int y);
int						hit_door(t_data *x, int index, double i, double j);
t_texture				*ft_lstnew_txt(char *attr, char *data);
int						is_door(char c);
int						hit_o(t_data x, double i, double j);
double					protect_angle(double angle);
void					animation(t_data *data);
void					*ft_malloc(int size, char c);
void					inisialise_angle(t_data *x, char p);
void					find_player(t_data *x);
void					door_keys(t_data *x);
unsigned int			create_rgb(int t, int r, int g);
int						check_textures(t_texture *txt, t_data *x);
void					move_w(t_data *x);
void					move_s(t_data *x);
void					move_d(t_data *x);
void					move_a(t_data *x);
void					slide_w(t_data *data);
void					slide_s(t_data *data);
void					slide_d(t_data *data);
void					slide_a(t_data *data);
int						check_distance(t_data *x);
int	mouse_move(int x, int y, t_data *data);
int	*x_mouse(void);
int	keyOnRelease(int key, t_data *x);
int	keyOnPres(int key, t_data *x);
void	init_keys(t_data *x);
void	init_textures(t_data *data);
char	*get_name_animation(int i);
int	is_textures(char *str);
#endif