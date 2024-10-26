/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:41:49 by cmaami            #+#    #+#             */
/*   Updated: 2024/09/18 23:13:12 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_libft(const char *s1)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	str = ft_malloc(sizeof(*s1) * (len + 1), 'a');
	if (!str)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
