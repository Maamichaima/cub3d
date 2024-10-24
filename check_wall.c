/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:49:29 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 14:07:17 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_wall(t_data x, double i, double j)
{
	int	a;
	int	b;

	if (i < 0 || i > (x.width * SCALE) || j < 0 || j > (x.height * SCALE))
		return (0);
	a = (int)(i / SCALE);
	b = (int)(j / SCALE);
	if (x.map[b][a] == '1')
	{
		return (1);
	}
	return (0);
}

int	hit_door(t_data *x, int index, double i, double j)
{
	int	a;
	int	b;

	if (i < 0 || i > (x->width * SCALE) || j < 0 || j > (x->height * SCALE))
		return (0);
	a = (int)(i / SCALE);
	b = (int)(j / SCALE);
	if (x->map[b][a] == 'd')
		return (1);
	return (0);
}

int	hit_o(t_data x, double i, double j)
{
	int	a;
	int	b;

	if (i < 0 || i > (x.width * SCALE) || j < 0 || j > (x.height * SCALE))
		return (0);
	a = (int)(i / SCALE);
	b = (int)(j / SCALE);
	if (x.map[b][a] == 'O')
		return (1);
	return (0);
}
