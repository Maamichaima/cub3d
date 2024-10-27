/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:11:25 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 13:54:18 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_player(char c)
{
	if (c == 'E' || c == 'N' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	check_player(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

t_texture	*ft_lstnew_txt(char *attr, char *data)
{
	t_texture	*l;

	l = ft_malloc(sizeof(t_texture), 'a');
	if (!l)
		return (NULL);
	l->attr = attr;
	l->data = data;
	l->next = NULL;
	return (l);
}
