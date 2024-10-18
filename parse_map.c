/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:26:19 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/02 20:36:09 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cub3d.h"

char **fillBlanks(t_data x)
{
	size_t i = 0;
	char **copie_map;

	copie_map = malloc(sizeof(char *) *( x.height + 1));
	
	//printf("%s\n", x.map[x.height - ]);
	while(i < x.height)
	{
		//printf("%s \n", x.map[i]);
		copie_map[i] = ft_calloc(x.width + 1, 1);
		ft_strlcpy(copie_map[i], x.map[i], ft_strlen(x.map[i]) + 1);
		i++;
	}
	copie_map[i] = NULL;
	return copie_map;
}

int	smya(char c)
{
	if(c != '1' && c != '0' && !is_player(c)&& !is_door(c))
	{
		// printf("hhhh\n");
		return 1;
	}
	return 0;
}

int check_next_to_zero(char **tab, size_t i, size_t j, t_data x)
{
	if(i <= 0 || i >= (x.height - 1) || j <= 0 || j >= (x.width - 1))
		return 1;
	if(tab[i][j] == 'd')
		return(check_next_to_door(tab,i,j));
	if(smya(tab[i - 1][j]) || smya(tab[i][j - 1]) || smya(tab[i + 1][j]) ||smya(tab[i][j + 1]))
		return 1;
	return 0;
}

int check_zero_in_map(char **tab, t_data x)
{
	int i = 0;
	int j = 0;

	while(tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			if((tab[i][j] == '0' || is_player(tab[i][j])|| is_door(tab[i][j]))&& check_next_to_zero(tab, i, j, x))
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

int check_start_map(char *ligne)
{
    int i = 0;

    ligne = skip_white_spaces(ligne);
    if(ligne[i] && ligne[i] == '1')
        return 0;
    return 1;
}
