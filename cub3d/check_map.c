/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:14:22 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/24 14:14:54 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

// int	is_door(char c)
// {
// 	if (c == 'd')
// 		return (1);
// 	return (0);
// }

int	smya(char c)
{
	if (c != '1' && c != '0' && !is_player(c))
		return (1);
	return (0);
}

// int	check_doors(char **tab, size_t i, size_t j)
// {
// 	if (!((tab[i - 1][j] == '1' && tab[i + 1][j] == '1') || (tab[i][j
// 				- 1] == '1' && tab[i][j + 1] == '1')))
// 		return (1);
// 	return (0);
// }
