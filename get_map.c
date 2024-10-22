/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:14:30 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/18 16:03:08 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cub3d.h"

int is_player(char c)
{
	if(c == 'E' || c == 'N' || c == 'S' || c == 'W')
		return 1;
	return 0;
}

int	checkPlayer(char **map)
{
	int i = 0;
	int j = 0;
	int count = 0;

	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(is_player(map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if(count == 1)
		return 1;
	else
		return 0;
}

t_texture *get_path(char *line)
{
    t_texture *info = malloc(sizeof(t_texture));
    char *tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
    char *buffer = malloc(sizeof(char) * ft_strlen(line) + 1);
    int i = 0 ;
    int j = 0 ;

    line = skip_white_spaces(line);
    while(line  && line[i] != 32)
        tmp[j++] = line[i++];
    tmp[j] = '\0';
    info->attr = ft_strdup_libft(tmp); //ft_strdup
    line = skip_white_spaces(line + i);
    j = 0;
    i = 0;
    while(line && line[i] != '\0' && line[i] != '\n') 
        buffer[j++] = line[i++];
    buffer[j] = '\0';
    info->data =ft_strdup_libft(ft_strtrim(buffer, " \t\n"));//ft_strdup
    info->next = NULL; 
    return(info);
}

t_texture	*ft_lstnew_txt(char *attr, char *data)
{
	t_texture	*l;

	l = malloc(sizeof(t_texture));
	if (!l)
		return (NULL);
	l->attr = attr;
	l->data = data;
	l->next = NULL;
	return (l);
}
t_texture *get_texture(int fd)
{
    char *line;
    int i = 0;
    t_texture *texture;
    t_texture *info;
    texture = NULL;
    line = get_next_line(fd);
	
			// puts(line);
    while(line && check_start_map(line))
    {
        i = 0;
        line = skip_white_spaces(line);
        if(line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == 'F' || line[i] == 'C' || line[i] != '\0')
        {   
            info =  get_path(line);
			// puts(info->attr);
			// puts(info->data);
            ft_lstadd_back_txt(&texture, info);
        }
       	line = get_next_line(fd);
    }
    close(fd);
    // t_texture  *tmp = texture;
    // while(tmp)
    // {
    //    printf("%s   %s\n",tmp->attr,tmp->data);
    //     tmp = tmp->next;
    // }
	return texture;
}

char **read_map(char *av)
{
	int fd;
	char *ligne;
	char **map = NULL;
	int *size;
	int i = 0;

	fd = open(av, O_RDONLY);
	if(fd == -1)
	{	
		printf("map not existe\n");
		return(NULL);
	}
	else
	{
		size = count_length_width(av);
		map = malloc(sizeof(char*) * (size[1] + 1));
		if(!map)
			return NULL;
		while(i < size[1])
		{
			ligne = get_next_line(fd);
			map[i] = ligne;
			i++;
		}
		map[i] = NULL;
	}
	return map;
}

char **alloc_map(int size)
{
	char **map = NULL;


	map = malloc(sizeof(char*) * (size + 1));
	if(!map)
		return NULL;
	return map;
}
