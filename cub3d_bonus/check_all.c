/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:05:12 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 14:13:23 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_white_space(char c)
{
	if (c != '\t' && c != 32)
		return (0);
	return (1);
}

int	check_char_map(t_data *x)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < x->height)
	{
		j = 0;
		while (j < ft_strlen(x->map[i]))
		{
			if (x->map[i][j] != '0' && x->map[i][j] != '1'
				&& !is_player(x->map[i][j]) && !is_door(x->map[i][j])
				&& !is_white_space(x->map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_all(t_data *x)
{
	int		fd;
	char	**c;

	fd = open(x->file_map, O_RDONLY);
	if (fd == -1)
	{
		printf("%s", x->file_map);
		free_exit(" not exist");
	}
	x->texture = get_texture(fd);
	c = fill_blanks(*x);
	x->map = c;
	if (check_char_map(x) && check_player(x->map) && check_zero_in_map(c, *x)
		&& check_textures(x->texture, x))
	{
		return (1);
	}
	else
	{
		free_exit("map not valide");
		return (0);
	}
}
