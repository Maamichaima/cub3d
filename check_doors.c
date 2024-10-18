#include "Cub3d.h"

int is_door(char c)
{
    if(c == 'd')
		return 1;
	return 0;
}

int	check_next_to_door(char **tab, size_t i, size_t j)
{
	if(!((tab[i - 1][j]  == '1' && tab[i + 1][j] == '1') || (tab[i][j - 1] == '1' && tab[i][j + 1] == '1')))
		return(1);
	return(0);
}