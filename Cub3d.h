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
# include <math.h>

#define SCALE 30
#define WIDTH 
#define LENGTH
#define PI 3.14
#define LIGNE_OF_PLAYER 50

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

typedef struct s_data
{
	void 	*mlx_ptr;
	char 	**map;
	void 	*mlx_win;
	size_t 	height;
	size_t 	width;
	int 	rayon;
	t_player player;
	t_image	 image;
} t_data;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int key_hook(int key, t_data *x);
char **read_map(char *av);
int *count_length_width(char *av);
void find_player(t_data *x);
void delete_player_in_map(t_data *x);
void draw(t_data x);
void put_mini_cyrcle(t_data x, int j, int i);
void color_one_square(int start_x, int start_y, void *x);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


#endif