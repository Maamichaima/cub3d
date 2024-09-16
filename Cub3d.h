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
# include "libft/libft.h"
#define SCALE 30
#define WIDTH 
#define LENGTH

typedef struct s_data
{
	void *mlx_ptr;
	char **map;
	void *mlx_win;
	size_t height;
	size_t width;
} t_data;

typedef struct s_texture
{
	char *attr;
	char *data;
} t_texture;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	get_texture(int fd);
t_texture	get_path(char *line);
int *count_length_width(char *av);
int check_map(t_data x);
int  valid_characters(char map, int *count);
void    check_characters(t_data x);

#endif