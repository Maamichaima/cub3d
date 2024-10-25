/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:00:13 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 19:57:15 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ls1;
	int		ls2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	p = ft_malloc(sizeof(char) * (ls1 + ls2 + 1), 'a');
	if (!p)
		return (NULL);
	p[0] = '\0';
	ft_strlcat(p, s1, ls1 + 1);
	ft_strlcat(p, s2, ls1 + ls2 + 1);
	return (p);
}
