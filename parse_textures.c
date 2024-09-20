
#include "Cub3d.h"

//  int check_map(t_data x)
//  {
//     char **p;
//     int i = 1;
//     int j = 0;
//     int valid = 1;
//     p = x.map;
//     while(p[0][j] != '\n')
//     {
//         if(p[0][j] != '1' && p[0][j] != 32)
//         {
//             printf("  1st con     ");
//             valid = 0;
//             break;
//         }
//         j++;
//     }
//     j = 0;
  
//     while(p[i] && i <( x.height - 1))
//     {
//         j = 0;
//         while(p[i][j] == 32)
//             j++;
//         if(p[i][j] != '1')
//         {
//             printf("  2nd con   %d  " ,i);
//             valid = 0;
//             break;
//         }
//         while(p[i][j] != '\n' && p[i][j] != '\0')
//             j++;
//         if(p[i][j - 1] != '1')
//         {   
//             printf("  3rd con    %d ",i);
//             valid = 0;
//             break;
//         }
//         i++;
//     }
//     j = 0;
//     while(p[x.height - 1][j] != '\0' && p[i][j] != '\n')
//     {
//         if(p[x.height - 1][j] != '1' && p[x.height - 1][j] != 32 )
//         {
//             printf("  4th con     ");
//             valid = 0;
//             break;
//         }
//         j++;
//     }
//     return valid;
// }


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
    int i = 0;
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
    return(correct_map(x));
}

char    **correct_map(t_data *x)
{
    int i ;
    int j;
    int k;
    char **tb;
    char **tmp; 
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
   // printf("%s\n",x->map[k]);
    return(x->map);
}