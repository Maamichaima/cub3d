/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:25:03 by cmaami            #+#    #+#             */
/*   Updated: 2024/10/10 16:24:20 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int  valid_characters(char map, int *count)
{  
    if((map == 'N' || map == 'S' || map == 'W' || map == 'E') && *count  == 0)
        *count += 1;
    else
        return(0);
    return(1);
}
void    check_characters(t_data x)
{
    char **map;
    int i, j,count = 0;
    map = x.map;

    i =0;

    while(map[i])
    {
        j =0;
        while(map[i][j] != '\n' && map[i][j] != '\0')
        {
            if(map[i][j] == '0' || map[i][j] == '1' || map[i][j] == 32 || valid_characters(map[i][j],&count) == 1)
                j++;
            else
            {   
                printf("NOT VALID %d\n",count);
                break;
            }
        }
        i++;
    }
    if(count == 0)
         printf("NOT VALID %d\n",count);
}

char    **get_map(int fd, t_data *x)
{
    char *line ;
    int j = 0;
    if(x->map == NULL)
        return(NULL);
   
    line = get_next_line(fd);

    while(line && check_start_map(line))
        line = get_next_line(fd);
    while(line)
    {
        x->map[j] = line;
        line = get_next_line(fd);
        j++;
    }
    x->map[j] = NULL;
    return(x->map);
}

char    **correct_map(t_data *x)
{
    int i ;
    int j;
    int k;
    char **tb;
    i = 0;
    k = 0;
   
    tb = x->map;
    while(tb[i])
    {
        j = 0;
        while(tb[i][j] == 32) // white spaces 
            j++;
        if(tb[i][j] == '1')
        {
            x->map[k] = tb[i];
            k++;
        }
        i++;
    }
    x->map[k] = NULL;
    return(x->map);
}
