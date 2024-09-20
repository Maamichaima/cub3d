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
	// if(fd == -1)
	// 	printf("map not existe\n");
	while(1)
	{
		ligne = get_next_line(fd);
		if (!ligne || !check_start_map(ligne))
			break ;
	}
	while(ligne)
	{	
		if(ft_strlen(ligne) >= length)
			length = ft_strlen(ligne);
		width++;
		free(ligne);
		ligne = get_next_line(fd);
	}
	t[0] = length;
	t[1] = width;
	//printf("%d  %d \n", t[0], t[1]);
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
	{	
		printf("map not existe\n");
		return(NULL);
	}
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

char **alloc_map(int size)
{
	char **map = NULL;

	map = malloc(sizeof(char*) * (size + 1));
	if(!map)
		return NULL;
	return map;
}

void inisialise(t_data *x, char *av)
{
	int *t;

	t = count_length_width(av);
	x->mlx_ptr = mlx_init();
	x->width = t[0];
	x->height = t[1];
	x->map = alloc_map(x->height);
	x->file_map = av;
	
}

// int check_all()
// {

// }
int main(int ac, char **av)
{
	t_data x;
	inisialise(&x, av[1]);
	check_all(&x);
}
// int main(int ac, char **av)
// {
// 	t_data x;
// 	int i = 0;
// 	 int fd = open(av[1], O_RDONLY);
// 	char *line;
// 	int rt;
// 	 inisialise(&x, av[1]);
	//  rt = check_map(x);
	//  check_characters(x);
	//  printf("%d  %d\n",x.width,x.height);
	// x.mlx_win = mlx_new_window(x.mlx_ptr, x.width * SCALE, x.height * SCALE, "Cub3D");
	// c(x);
	// while (x.map[i])
	// {
	// 	printf("%s", x.map[i]);
	// 	i++;
	// }
	// get_texture(fd);
	// get_map(fd ,&x);
	// correct_map(&x);
	//check_zero_in_map(fillBlanks(x), x);
	// printf("\n\nnew map \n");
	// while (x.map[i])
	// {
	// 	printf("%s", x.map[i]);
	// 	i++;
	//  }
	 //mlx_loop(x.mlx_ptr);
//}
