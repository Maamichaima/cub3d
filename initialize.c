/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:40:12 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/23 19:42:00 by maamichaima      ###   ########.fr       */
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
