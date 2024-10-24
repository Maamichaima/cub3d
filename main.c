/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:24:17 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/23 19:46:09 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_textures(char *str)
{
	if (!ft_strcmp(str, "EA") || !ft_strcmp(str, "NO") || !ft_strcmp(str, "WE")
		|| !ft_strcmp(str, "SO") || !ft_strcmp(str, "d"))
		return (1);
	return (0);
}

int	ft_close(t_data *x)
{
	mlx_destroy_image(x->mlx_ptr, x->image.ptr_img);
	mlx_destroy_window(x->mlx_ptr, x->mlx_win);
	exit(0);
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
