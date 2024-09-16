#include "Cub3d.h"

void inisialise(t_data *x, char *n)
{
	int *t;

	t = count_length_width(n);
	x->mlx_ptr = mlx_init();
	x->map = read_map(n);
	x->width = t[0];
	x->height = t[1];
	x->rayon = SCALE / 2;
	find_player(x);
	x->player.angle = 0;// E W N S
	x->player.dx = cos(x->player.angle);
	x->player.dy = sin(x->player.angle);
}

int main(int ac, char **av)
{
	t_data x;
	int i = 0;

	inisialise(&x, av[1]);
	delete_player_in_map(&x);
	x.mlx_win = mlx_new_window(x.mlx_ptr, x.width * SCALE, x.height * SCALE, "Cub3D");
	x.image.ptr_img = mlx_new_image(x.mlx_ptr, x.width * SCALE, x.height * SCALE);
	x.image.addr = mlx_get_data_addr(x.image.ptr_img, &x.image.bits_per_pixel,
				&x.image.line_length, &x.image.endian);
	draw(x);
	mlx_key_hook(x.mlx_win, key_hook, &x);
	// while (x.map[i])
	// {
	// 	printf("%s \n", x.map[i]);
	// 	i++;
	// }
	mlx_loop(x.mlx_ptr);
}
