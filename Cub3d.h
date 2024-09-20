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
	char *file_map;
} t_data;

typedef struct s_texture
{
	char *attr;
	char *data;
	struct s_texture *next;
} t_texture;

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
int check_next_to_zero(char **tab, int i, int j, t_data x);
int check_zero_in_map(char **tab, t_data x);
char **alloc_map(int size);
int check_start_map(char *ligne);
int    check_textures(t_texture *txt);
void inisialise(t_data *x, char *n);
int check_all(t_data *x);
int possible_color(char *attr);
#endif