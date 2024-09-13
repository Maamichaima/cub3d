#include "Cub3d.h"

int *count_length_width(char *av)
{
	int *t = malloc(sizeof(int) * 2);
	size_t length;
	size_t width;
	int fd;
	char *ligne;

	length = 0;
	width = 0;
	fd = open(av, O_RDONLY);
	length = 0;
	if(fd == -1)
		printf("map not existe\n");
	while(1)
	{
		ligne = get_next_line(fd);
		if (!ligne)
			break ;
		if(ft_strlen(ligne) >= length)
			length = ft_strlen(ligne);
		width++;
		free(ligne);
	}
	t[0] = length;
	t[1] = width;
	close(fd);
	return t;
}

// void	my_mlx_pixel_put(t_fractol *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

void color_one_square(int start_x, int start_y, void *mlx_ptr, void *win_ptr)
{
    int i = 0;
	int j = 0;
    int color = 255;

    while (i < 50)
    {
		j = 0;
        while (j < 50)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, start_x + i, start_y + j, color);
			j++;
        }
		i++;
    }
}

void c(t_data x)
{
	int i = 0;
	int j = 0;
	int a;
	int b;

	while(i < (x.height * SCALE))
	{
		j = 0;
		while(j < (x.width * SCALE))
		{
			a = i / SCALE;
			b = j / SCALE;
			if(a >= 0 && a < x.height && b >= 0 && b < x.width && x.map[a][b] == '1')
            	mlx_pixel_put(x.mlx_ptr, x.mlx_win, j, i, 0xe0d5d9);
			else if(a >= 0 && a < x.height && b >= 0 && b < x.width && x.map[a][b] == '0')
            	mlx_pixel_put(x.mlx_ptr, x.mlx_win, j, i, 0x215dbf);
			j++;
		}
		i++;
	}
}

char **read_map(char *av)
{
	int fd;
	char *ligne;
	char **map = NULL;
	int *size;
	int i = 0;

	fd = open(av, O_RDONLY);
	if(fd == -1)
		printf("map not existe\n");
	else
	{
		size = count_length_width(av);
		// printf("%d   %d\n", size[0], size[1]);
		map = malloc(sizeof(char*) * (size[1] + 1));
		if(!map)
			return NULL;
		while(i < size[1])
		{
			ligne = get_next_line(fd);
			map[i] = ligne;
			i++;
		}
		map[i] = NULL;
	}
	return map;
}

void inisialise(t_data *x, char *n)
{
	int *t;

	t = count_length_width(n);
	x->mlx_ptr = mlx_init();
	x->map = read_map(n);
	x->width = t[0];
	x->height = t[1];
}

int main(int ac, char **av)
{
	t_data x;
	int i = 0;

	inisialise(&x, av[1]);
	x.mlx_win = mlx_new_window(x.mlx_ptr, x.width * SCALE, x.height * SCALE, "Cub3D");
	c(x);
	while (x.map[i])
	{
		printf("%s \n", x.map[i]);
		i++;
	}
	mlx_loop(x.mlx_ptr);
}
