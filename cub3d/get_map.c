/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:14:30 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/23 19:13:44 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_texture	*get_path(char *line)
{
	t_texture	*info;
	char		*tmp;
	char		*buffer;
	int			i;
	int			j;

	info = ft_malloc(sizeof(t_texture), 'a');
	tmp = ft_malloc(sizeof(char) * ft_strlen(line) + 1, 'a');
	buffer = ft_malloc(sizeof(char) * ft_strlen(line) + 1, 'a');
	i = 0;
	j = 0;
	line = skip_white_spaces(line);
	while (line[i] && line[i] != 32)
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	info->attr = ft_strdup_libft(tmp);
	line = skip_white_spaces(line + i);
	j = 0;
	i = 0;
	while (line && line[i] != '\0' && line[i] != '\n')
		buffer[j++] = line[i++];
	buffer[j] = '\0';
	info->data = ft_strdup_libft(ft_strtrim(buffer, " \t\n"));
	info->next = NULL;
	return (info);
}

void	set_map_data(char **map, int fd, int size)
{
	int		i;
	char	*ligne;

	i = 0;
	while (i < size)
	{
		ligne = get_next_line(fd);
		map[i] = ligne;
		i++;
	}
	map[i] = NULL;
}

char	**read_map(char *av)
{
	int		fd;
	char	**map;
	int		*size;
	int		i;

	map = NULL;
	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		printf("%s", av);
		free_exit(" not exist");
	}
	else
	{
		size = count_length_width(av);
		map = ft_malloc(sizeof(char *) * (size[1] + 1), 'a');
		if (!map)
			return (NULL);
		set_map_data(map, fd, size[1]);
	}
	return (map);
}

char	**alloc_map(int size)
{
	char	**map;

	map = NULL;
	map = ft_malloc(sizeof(char *) * (size + 1), 'a');
	if (!map)
		return (NULL);
	return (map);
}
