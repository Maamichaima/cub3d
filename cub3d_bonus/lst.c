/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:15:41 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/21 15:16:30 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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
