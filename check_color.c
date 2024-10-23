/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:00:58 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/22 19:26:32 by maamichaima      ###   ########.fr       */
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

int	check_is_int(char *str)
{
	int	i;
	int	nb;

	i = 0;
	if (!str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (ft_strlen(str) > 4 || !str[i])
		return (0);
	// printf("---%s---\n", str);
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	i = 0;
	nb = ft_atoi(str);
	if (nb < 0 || nb > 255)
		return (0);
	return (1);
}

int	check_color(char *ligne, char *att)
{
	char	**tab;
	int		i;
	int		retu;

	if (!possible_color(att))
		return (0);
	i = 0;
	if (count_comma(ligne) != 2)
		return (0);
	tab = ft_split(ligne, ',');
	while (tab[i])
	{
		if ((check_is_int(ft_strtrim(tab[i], " \t\n"))) == 0)
		{
			retu = 0;
			break ;
		}
		i++;
	}
	retu = 1;
	if (i != 3)
		return (0);
	return (retu);
}

char	*skip_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (str + i);
}
