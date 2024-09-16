#include "Cub3d.h"


 t_texture get_path(char *line)
 {
    t_texture info;
    char *tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
    int i = 0 ;
    int j = 0 ;

        while(line  && line[i] != 32)
            tmp[j++] = line[i++];
        tmp[j] = '\0';
        info.attr = strdup(tmp); //ft_strdup
        tmp = tmp + j;
        j = 0;
        i++;
        while(line && line[i] != '\0' && line[i] != '\n')
            tmp[j++] = line[i++];
        tmp[j] = '\0';
        info.data = strdup(tmp); // ft_strdup
        return(info);
 }
void get_texture(int fd)
{
    char *line;
    t_texture info;
    line = get_next_line(fd);
    while(line)
    {
        if(line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
            info =  get_path(line) ;
        else
        {
            line = get_next_line(fd);
            continue;
        }
       line = get_next_line(fd);
    }
}
 int check_map(t_data x)
 {
    char **p;
    int i = 1;
    int j = 0;
    int valid = 1;
    p = x.map;
    while(p[0][j] != '\n')
    {
        if(p[0][j] != '1' && p[0][j] != 32 )
        {
            printf("  1st con     ");
            valid = 0;
            break;
        }
        j++;
    }
    j = 0;
  
    while(p[i] && i <( x.height - 1))
    {
        j = 0;
        while(p[i][j] == 32)
            j++;
        if(p[i][j] != '1')
        {
            printf("  2nd con   %d  " ,i);
            valid = 0;
            break;
        }
        while(p[i][j] != '\n' && p[i][j] != '\0')
            j++;
        if(p[i][j - 1] != '1')
        {   
            printf("  3rd con    %d ",i);
            valid = 0;
            break;
        }
        i++;
    }
    j = 0;
    while(p[x.height - 1][j] != '\0' && p[i][j] != '\n')
    {
        if(p[x.height - 1][j] != '1' && p[x.height - 1][j] != 32 )
        {
            printf("  4th con     ");
            valid = 0;
            break;
        }
        j++;
    }
    return valid;
 }
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
             {   printf("NOT VALID %d\n",count);
                break;
            }
            
        }
        i++;
    }
    if(count == 0)
         printf("NOT VALID %d\n",count);
}