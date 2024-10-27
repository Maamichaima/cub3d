/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:44:37 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/23 19:46:15 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	key_on_pres(int key, t_data *x)
{
	if (key == 13)
		x->keys[W] = 1;
	if (key == 1)
		x->keys[S] = 1;
	if (key == 2)
		x->keys[D] = 1;
	if (key == 0)
		x->keys[A] = 1;
	if (key == 124)
		x->keys[R] = 1;
	if (key == 123)
		x->keys[L] = 1;
	if (key == 53)
		x->keys[ESC] = 1;
	if (key == 31)
		x->keys[O] = 1;
	if (key == 8)
		x->keys[C] = 1;
	if (key == 46 && x->ff < 21)
		x->ff = 22;
	return (0);
}

int	key_on_release(int key, t_data *x)
{
	if (key == 13)
		x->keys[W] = 0;
	if (key == 1)
		x->keys[S] = 0;
	if (key == 2)
		x->keys[D] = 0;
	if (key == 0)
		x->keys[A] = 0;
	if (key == 124)
		x->keys[R] = 0;
	if (key == 123)
		x->keys[L] = 0;
	if (key == 65307)
		x->keys[ESC] = 0;
	return (0);
}

void	init_keys(t_data *x)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		x->keys[i] = 0;
		i++;
	}
}
