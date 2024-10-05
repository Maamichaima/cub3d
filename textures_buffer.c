#include "Cub3d.h"

void    get_textures_buffer(t_data *data)
{
    //char	*relative_path = "./test.xpm";
     // printf("%s\n", data->texture.data);
    data->texture.ptr_img = mlx_xpm_file_to_image(data->mlx_ptr,data->texture.data,&data->texture.width,&data->texture.height);
    if(!data->texture.ptr_img)
        printf("Image reading has failed \n");
    //printf("width=%d   height=%d\n",data->texture.width,data->texture.height);



}