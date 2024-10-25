/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:14:00 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/23 19:42:51 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	put_animation(t_data *data, int i, int j, t_texture t)
{
	double	a;
	double	b;
	double	scale_width;
	double	scale_height;
	int		color;

	scale_height = HEIGHT / (double)t.height;
	scale_width = WIDTH / (double)t.width;
	a = i / scale_width;
	b = j / scale_height;
	color = my_mlx_pixel_get(t.img, a, b);
	if (color > 0 && i > 0 && i < WIDTH && j > 0 && j < HEIGHT)
		my_mlx_pixel_put(data, i, j, color);
	j++;
}

void	animation(t_data *data)
{
	t_texture	t;
	int			i;
	int			j;

	j = 300;
	i = 0;
	t = data->animation[data->ff];
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_animation(data, i, j, t);
			j++;
		}
		i++;
	}
	data->ff++;
	if (data->ff == 21)
		data->ff = 0;
	else if (data->ff == 91)
		data->ff = 0;
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
