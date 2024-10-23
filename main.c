/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:24:17 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/23 00:03:46 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	inisialise_angle(t_data *x, char p)
{
	if (p == 'N')
		x->player.angle = 3 * PI / 2;
	else if (p == 'E')
		x->player.angle = 0;
	else if (p == 'S')
		x->player.angle = PI / 2;
	else if (p == 'W')
		x->player.angle = PI;
	x->player.dx = cos(x->player.angle);
	x->player.dy = sin(x->player.angle);
}


int	is_textures(char *str)
{
	if (!ft_strcmp(str, "EA") || !ft_strcmp(str, "NO") || !ft_strcmp(str, "WE")
		|| !ft_strcmp(str, "SO") || !ft_strcmp(str, "d"))
		return (1);
	return (0);
}

void init_image_animation(t_data *data)
{
	int i;
	
	i = 0;
	while (i < 91)
	{
		data->animation[i].ptr_img = mlx_xpm_file_to_image(data->mlx_ptr,
				data->animation[i].data, &data->animation[i].width,
				&data->animation[i].height);
		if (!data->animation[i].ptr_img)
			printf("Image reading has failed \n");
		data->animation[i].img.addr = mlx_get_data_addr(data->animation[i].ptr_img,
				&data->animation[i].img.bits_per_pixel,
				&data->animation[i].img.line_length,
				&data->animation[i].img.endian);
		i++;
	}
}

void	init_textures(t_data *data)
{
	t_texture	*t;
	t_texture	*new;
	int			i;

	t = data->texture;
	new = ft_lstnew_txt("d", "textures/door3.xpm");
	ft_lstadd_back_txt(&data->texture, new);
	while (t)
	{
		if (is_textures(t->attr))
		{
			t->ptr_img = mlx_xpm_file_to_image(data->mlx_ptr, t->data,
					&t->width, &t->height);
			if (!t->ptr_img)
				printf("Image reading has failed \n");
			t->img.addr = mlx_get_data_addr(t->ptr_img, &t->img.bits_per_pixel,
					&t->img.line_length, &t->img.endian);
		}
		t = t->next;
	}
	init_image_animation(data);
}

char	*get_name_animation(int i)
{
	char	*str;
	char	*num;

	str = ft_malloc(sizeof(char) * (24), 'a');
	if (!str)
		return (NULL);
	str = "animation/final";
	num = ft_itoa(i + 1);
	if (ft_strlen(num) == 1)
	{
		str = ft_strjoin(str, "00");
		str = ft_strjoin(str, num);
	}
	else
		str = ft_strjoin(str, num);
	str = ft_strjoin(str, ".xpm");
	return (str);
}

void	init_keys(t_data *x)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		x->keys[i] = 0;
		i++;
	}
}

void	init_data_animation(t_data *x)
{
	int	i;

	i = 0;
	while (i < 91)
	{
		x->animation[i].data = get_name_animation(i);
		i++;
	}
}

void	inisialise(t_data *x, char *av)
{
	int	*t;
	int	fd;
	int	i;

	t = count_length_width(av);
	x->mlx_ptr = mlx_init();
	x->width = t[0];
	x->height = t[1];
	x->map = alloc_map(x->height);
	x->file_map = av;
	fd = open(x->file_map, O_RDONLY);
	x->map = get_map(fd, x);
	x->rayon = SCALE / 2;
	x->num_rays = WIDTH;
	x->ray = ft_malloc(sizeof(t_ray) * WIDTH, 'a');
	init_keys(x);
	init_data_animation(x);
	x->ff = 0;
}

int	ft_close(t_data *x)
{
	mlx_destroy_image(x->mlx_ptr, x->image.ptr_img);
	mlx_destroy_window(x->mlx_ptr, x->mlx_win);
	exit(0);
}

int	keyOnPres(int key, t_data *x)
{
	if (key == 13) // XK_w)
		x->keys[W] = 1;
	if (key == 1) // XK_s)
		x->keys[S] = 1;
	if (key == 2) // XK_d)
		x->keys[D] = 1;
	if (key == 0) // XK_a)
		x->keys[A] = 1;
	if (key == 124) // XK_Right)
		x->keys[R] = 1;
	if (key == 123) // XK_Left)
		x->keys[L] = 1;
	if (key == 53)
		x->keys[ESC] = 1;
	if (key == 31)
		x->keys[O] = 1;
	if (key == 8)
		x->keys[C] = 1;
	if (key == 46 && x->ff < 21)
		x->ff = 22;
	return (0);
}

int	keyOnRelease(int key, t_data *x)
{
	if (key == 13) // XK_w)
		x->keys[W] = 0;
	if (key == 1) // XK_s)
		x->keys[S] = 0;
	if (key == 2) // XK_d)
		x->keys[D] = 0;
	if (key == 0) // XK_a)
		x->keys[A] = 0;
	if (key == 124) // XK_Right)
		x->keys[R] = 0;
	if (key == 123) // XK_Left)
		x->keys[L] = 0;
	if (key == 65307)
		x->keys[ESC] = 0;
	return (0);
}

int	*x_mouse(void)
{
	static int	x = 0;

	return (&x);
}

int	mouse_move(int x, int y, t_data *data)
{
	int static	c;

	if (c == 0)
	{
		*x_mouse() = x;
		c = 1;
	}
	if (x > *x_mouse())
	{
		data->player.angle += A_SPEED;
		if (data->player.angle >= 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dx = cos(data->player.angle);
		data->player.dy = sin(data->player.angle);
	}
	if (x < *x_mouse())
	{
		data->player.angle -= A_SPEED;
		if (data->player.angle < 0)
			data->player.angle = 2 * PI - data->player.angle;
		data->player.dx = cos(data->player.angle);
		data->player.dy = sin(data->player.angle);
	}
	*x_mouse() = x;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	x;

	inisialise(&x, av[1]);
	if (check_all(&x))
	{
		init_textures(&x);
		find_player(&x);
		x.mlx_win = mlx_new_window(x.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
		x.image.ptr_img = mlx_new_image(x.mlx_ptr, WIDTH, HEIGHT);
		x.image.addr = mlx_get_data_addr(x.image.ptr_img,
				&x.image.bits_per_pixel, &x.image.line_length, &x.image.endian);
		mlx_hook(x.mlx_win, 17, 0, &ft_close, &x);
		mlx_hook(x.mlx_win, 02, 1L << 0, keyOnPres, &x);
		mlx_hook(x.mlx_win, 6, 1L << 6, mouse_move, &x);
		mlx_hook(x.mlx_win, 03, 1L << 1, keyOnRelease, &x);
		mlx_loop_hook(x.mlx_ptr, draw, &x);
		mlx_loop(x.mlx_ptr);
	}
}
