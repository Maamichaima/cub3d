/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:38:16 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/15 18:38:18 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

char **read_map(char *av)
{
	int fd;
	char *ligne;
	char **map = NULL;
	int *size;
	int i = 0;

	fd = open(av, O_RDONLY);
	if(fd == -1)
		printf("map not existe\n");
	else
	{
		size = count_length_width(av);
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

// int *count_length_width(char *av)
// {
// 	int *t = malloc(sizeof(int) * 2);
// 	size_t length;
// 	size_t width;
// 	int fd;
// 	char *ligne;

// 	length = 0;
// 	width = 0;
// 	fd = open(av, O_RDONLY);
// 	length = 0;
// 	if(fd == -1)
// 		printf("map not existe\n");
// 	while(1)
// 	{
// 		ligne = get_next_line(fd);
// 		if (!ligne)
// 			break ;
// 		if(ft_strlen(ligne) >= length)
// 			length = ft_strlen(ligne);
// 		width++;
// 		free(ligne);
// 	}
// 	t[0] = length;
// 	t[1] = width;
// 	close(fd);
// 	return t;
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
			if(x->map[i][j] == 'E')
			{
				x->map[i][j] = '0';
				break;
			}
			j++;
		}
		i++;
	}
}

void find_player(t_data *x)
{
	int i = 0;
	int j = 0;

	while(i < x->width)
	{
		j = 0;
		while(j < x->height)
		{
			if (x->map[i][j] == 'E')
			{
				printf("x --> %d  y --> %d \n", i ,j);
				x->player.x = (i * SCALE) + SCALE / 2;
				x->player.y = (j * SCALE) + SCALE / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}
