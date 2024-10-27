/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:16:34 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/24 14:42:56 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	possible_textures(char *attr)
{
	if (ft_strcmp(attr, "NO") == 0 || ft_strcmp(attr, "WE") == 0
		|| ft_strcmp(attr, "EA") == 0 || ft_strcmp(attr, "SO") == 0)
		return (1);
	return (0);
}

int	check_extention(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i])
		return (0);
	if (ft_strcmp(str + i, ".xpm") == 0)
		return (1);
	return (0);
}

int	valid_files(char *file, char *att)
{
	int	fd;

	if (!possible_textures(att) || !check_extention(file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);
}

int	check_textures_is_duplicate(char *data, t_texture *t)
{
	int	count;

	count = 0;
	while (t)
	{
		if (ft_strcmp(t->attr, data) == 0)
			count++;
		t = t->next;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	check_textures(t_texture *txt, t_data *x)
{
	t_texture	*tmp;
	int count;

	tmp = txt;
	count = 0;
	while (txt)
	{
		if (!valid_files(ft_strtrim(txt->data, " \t\n"), txt->attr)
			&& !check_color(txt->data, txt->attr, x))
			return (0);
		if (!check_textures_is_duplicate(txt->attr, tmp))
			return (0);
			count++;
		txt = txt->next;
	}
	if(count != 6)
		return (0);
	return (1);
}
