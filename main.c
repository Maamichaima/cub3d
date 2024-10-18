/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:24:17 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/17 13:58:35 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


void delete_player_in_map(t_data *x)
{
	int i = 0;
	int j = 0;
	int *t = count_length_width("map.cub");

	while(i < t[1])
	{
		j = 0;
		while(j < t[0])
		{
			if(is_player(x->map[i][j]))
			{
				x->map[i][j] = '0';
				break;
			}
			j++;
		}
		i++;
	}
}

void inisialise_angle(t_data *x, char p)
{
	if(p == 'N')
		x->player.angle = 3 * PI / 2;
	else if(p == 'E')
		x->player.angle = 0;
	else if(p == 'S')
		x->player.angle = PI / 2;
	else if(p == 'W')
		x->player.angle = PI;
	x->player.dx = cos(x->player.angle);
	x->player.dy = sin(x->player.angle);
}
void find_player(t_data *x)
{
	int i = 0;
	int j = 0;

	while(x->map[i])
	{
		j = 0;
		while(x->map[i][j])
		{
			// printf("x --> %d  y --> %d \n", i ,j);
			if (is_player(x->map[i][j]))
			{
				inisialise_angle(x, x->map[i][j]);
				x->player.y = (i * SCALE) + SCALE / 2;
				x->player.x = (j * SCALE) + SCALE / 2;
				x->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int is_textures(char *str)
{
	if(!ft_strcmp(str, "EA") || !ft_strcmp(str, "NO") ||!ft_strcmp(str, "WE") ||!ft_strcmp(str, "SO"))
		return 1;
	return 0;
}

void init_textures(t_data *data)
{
	t_texture *t = data->texture;
	
	while(t)
	{
		if(is_textures(t->attr))
		{
			t->ptr_img = mlx_xpm_file_to_image(data->mlx_ptr, t->data, &t->width, &t->height);
			if(!t->ptr_img)
				printf("Image reading has failed \n");
			t->img.addr = mlx_get_data_addr(t->ptr_img, &t->img.bits_per_pixel, &t->img.line_length, &t->img.endian);
		}
		t = t->next;
	}
}

void inisialise(t_data *x, char *av)
{
	int *t;
	int fd;

	t = count_length_width(av);
	x->mlx_ptr = mlx_init();
	x->width = t[0];
	x->height = t[1];
	x->map = alloc_map(x->height);
	x->file_map = av;
	fd = open(x->file_map, O_RDONLY);
	x->map = get_map(fd ,x);
	x->rayon = SCALE / 2;
	x->num_rays = WIDTH;
	x->ray = malloc(sizeof(t_ray) * WIDTH);
	// printf("%f \n", x->num_rays);
	int i = 0;
	while(i < 6)
	{
		x->keys[i] = 0;
		i++;
	}
}
int	ft_close(t_data *x)
{
	mlx_destroy_image(x->mlx_ptr, x->image.ptr_img );
	mlx_destroy_window(x->mlx_ptr, x->mlx_win);
	exit(0);
}
int	keyOnPres(int key, t_data *x)
{
	if(key == 13)//XK_w)
		x->keys[W] = 1;
	if(key == 1)//XK_s)
		x->keys[S] = 1;
	if(key == 2)//XK_d)
		x->keys[D] = 1;
	if(key == 0)//XK_a)
		x->keys[A] = 1;
	if(key == 124)//XK_Right)
		x->keys[R] = 1;
	if(key == 123)//XK_Left)
		x->keys[L] = 1;
	if(key == 65307)
		x->keys[ESC] = 1;
	return 0;
}
int	keyOnRelease(int key, t_data *x)
{
	if(key == 13)//XK_w)
		x->keys[W] = 0;
	if(key == 1)//XK_s)
		x->keys[S] = 0;
	if(key == 2)//XK_d)
		x->keys[D] = 0;
	if(key == 0)//XK_a)
		x->keys[A] = 0;
	if(key == 124)//XK_Right)
		x->keys[R] = 0;
	if(key == 123)//XK_Left)
		x->keys[L] = 0;
	if(key == 65307)
		x->keys[ESC] = 0;
	return 0;
}

int	*x_mouse(void)
{
	static int	x = 0;

	return (&x);
}

int mouse_move(int x, int y, t_data *data)
{
	int static c = 0;
    if(c == 0)
	{
		*x_mouse() = x;
		c = 1;
	}
	if(x > *x_mouse())
	{
		data->player.angle += A_SPEED;
		if(data->player.angle >= 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dx = cos(data->player.angle);
		data->player.dy = sin(data->player.angle);
	}
	if(x < *x_mouse())
	{
		data->player.angle -= A_SPEED;
		if(data->player.angle < 0)
			data->player.angle = 2 * PI - data->player.angle;
		data->player.dx = cos(data->player.angle);
		data->player.dy = sin(data->player.angle);
	}
	*x_mouse() = x;
    return (0);
}

int main(int ac, char **av)
{
	t_data x;
	inisialise(&x, av[1]);
	if(check_all(&x))
	{
		init_textures(&x);
		find_player(&x);
		x.mlx_win = mlx_new_window(x.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
		x.image.ptr_img = mlx_new_image(x.mlx_ptr, WIDTH, HEIGHT);
		x.image.addr = mlx_get_data_addr(x.image.ptr_img, &x.image.bits_per_pixel,
					&x.image.line_length, &x.image.endian);
		// mlx_key_hook(x.mlx_win, key_hook, &x);
		mlx_hook(x.mlx_win, 17, 0, &ft_close, &x);
		mlx_hook(x.mlx_win, 02, 1L<<0, keyOnPres, &x);
		mlx_hook(x.mlx_win, 6, 1L << 6, mouse_move, &x);
		mlx_hook(x.mlx_win, 03, 1L<<1, keyOnRelease, &x);
		mlx_loop_hook (x.mlx_ptr, draw, &x);
		// get_textures_buffer(&x);
		mlx_loop(x.mlx_ptr);
	}
	// int i = 0;
	// while(x.map[i])
	// {
	// 	printf("%s", x.map[i]);
	// 	i++;
	// }
}
