#include "Cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (ss1[i] != '\0' && ss2[i] != '\0' && ss1[i] == ss2[i])
	{
		i++;
	}
	return (ss1[i] - ss2[i]);
}

char *skip_white_spaces(char *str)
{
    int i;

    i = 0 ;
    while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    return(str + i);
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
    info->attr = strdup(tmp); //ft_strdup
    line = skip_white_spaces(line + i);
    j = 0;
    i = 0;
    while(line && line[i] != '\0' && line[i] != '\n') 
        buffer[j++] = line[i++];
    buffer[j] = '\0';
    info->data = strdup(buffer);//ft_strdup
    info->next = NULL; 
    return(info);
}

t_texture	*ft_lstlast_txt(t_texture *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_txt(t_texture **lst, t_texture *new)
{
	t_texture	*t;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast_txt(*lst);
		t->next = new;
	}
}

int possible_textures(char *attr)
{
    if(ft_strcmp(attr,"NO") == 0 || ft_strcmp(attr,"WE") == 0 || ft_strcmp(attr,"EA") == 0 || 
    ft_strcmp(attr,"SO") == 0 )
        return(1);
    return(0);
}
int possible_color(char *attr)
{
    if(ft_strcmp(attr,"C") == 0 || ft_strcmp(attr,"F") == 0 )
        return(1);
    return(0);
}
int     valid_files(char *file, char *att)
{
	if(!possible_textures(att))
		return 0;
    int fd;
    fd = open(file, O_RDONLY);
    if(fd == -1)
        return(0);
    return(1);
}
int    check_textures(t_texture *txt)
{
	int var = 0;
    while(txt)
    {
		// printf("%s  %s  \n", txt->attr, txt->data);
		// printf("%d   %d\n", valid_files(ft_strtrim(txt->data, " \t\n"), txt->attr) ,check_color(txt->data, txt->attr));
        if(!valid_files(ft_strtrim(txt->data, " \t\n"), txt->attr) && !check_color(txt->data, txt->attr))
		{
			puts("hhh");
			return 0;
		}

        // else
        //     return 0;
		// if(!(possible_color(txt->attr) && check_color(txt->data)) || 
		// !(possible_textures(txt->attr)  && valid_files(ft_strtrim(txt->data, " \t\n"))))
		// 	return 0;
        txt =txt->next;
    }
	// printf("%d\n",var);
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

t_texture *get_texture(int fd)
{
    char *line;
    int i = 0;
    t_texture *texture;
    t_texture *info;
    texture = NULL;
    line = get_next_line(fd);
    while(line && check_start_map(line))
    {
        // printf("%s ",line);
        i = 0;
        line = skip_white_spaces(line);
        if(line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == 'F' || line[i] == 'C' || line[i] != '\0')
        {   
            info =  get_path(line);
            ft_lstadd_back_txt(&texture,info);
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

