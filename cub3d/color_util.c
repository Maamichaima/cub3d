/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:07:15 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/23 17:08:12 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	possible_color(char *attr)
{
	if (ft_strcmp(attr, "C") == 0 || ft_strcmp(attr, "F") == 0)
		return (1);
	return (0);
}

int	count_comma(char *ligne)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ligne[i])
	{
		if (ligne[i] == ',')
			count++;
		i++;
	}
	return (count);
}

unsigned int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
