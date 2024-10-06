#include "Cub3d.h"

unsigned int my_mlx_pixel_get(t_image image, int x, int y)
{
	char	*dst;

	dst = image.addr + (y * image.line_length + x * (image.bits_per_pixel / 8));
	return *((unsigned int*)dst);
}

void    get_textures_buffer(t_data *data)
{
	double scale_width;
	double scale_height;
	int i = 0;
	int j = 0;
	double a, b;

    data->texture->ptr_img = mlx_xpm_file_to_image(data->mlx_ptr, "texture->xpm",&data->texture->width,&data->texture->height);
	data->texture->img.addr = mlx_get_data_addr(data->texture->ptr_img, &data->texture->img.bits_per_pixel, &data->texture->img.line_length, &data->texture->img.endian);
    scale_height = HEIGHT / (double)data->texture->height;
    scale_width = WIDTH / (double)data->texture->width;
	if(!data->texture->ptr_img)
        printf("Image reading has failed \n");
	unsigned int color;
	while(i < WIDTH)
	{
		j = 0;
		while(j < HEIGHT)
		{
			a = i / scale_width;
			b = j / scale_height;
			color = my_mlx_pixel_get(data->texture->img, a, b);
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, i, j, color);
			// my_mlx_pixel_put(data, a, b, );
			j++;
		}
		i++;
	}
}