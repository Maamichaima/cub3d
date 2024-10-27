/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:38:16 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/22 20:12:56 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	delete_player_in_map(t_data *x)
{
	int	i;
	int	j;
	int	*t;

	i = 0;
	j = 0;
	t = count_length_width("map.cub");
	while (i < t[1])
	{
		j = 0;
		while (j < t[0])
		{
			if (is_player(x->map[i][j]))
			{
				x->map[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
}

void	find_player(t_data *x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (x->map[i])
	{
		j = 0;
		while (x->map[i][j])
		{
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

size_t	ft_strlen_map(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

void	get_width_height(size_t *width, size_t *length, int fd)
{
	char	*ligne;

	while (1)
	{
		ligne = get_next_line(fd);
		if (!ligne || !check_start_map(ligne))
			break ;
	}
	while (ligne)
	{
		if (ft_strlen_map(ligne) >= *length)
			*length = ft_strlen_map(ligne);
		(*width)++;
		ligne = get_next_line(fd);
	}
}

int	*count_length_width(char *av)
{
	int		*t;
	size_t	length;
	size_t	width;
	int		fd;

	t = ft_malloc(sizeof(int) * 2, 'a');
	length = 0;
	width = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		printf("%s", av);
		free_exit(" not exist");
	}
	length = 0;
	get_width_height(&width, &length, fd);
	t[0] = length;
	t[1] = width;
	close(fd);
	return (t);
}
