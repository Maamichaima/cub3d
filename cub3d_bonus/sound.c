/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:05:02 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/26 23:13:10 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	*play_sound(void *x)
{
	t_data	*data;

	data = (t_data *)x;
	data->sound_flag = 0;
	system("afplay ../sound.wav &");
	ft_usleep(500);
	data->sound_flag = 1;
	return (NULL);
}

void	*play_sound_animation(void *x)
{
	t_data	*data;

	data = (t_data *)x;
	data->sound_animation = 0;
	system("afplay ../Come-on-Let_s-go.wav");
	data->sound_animation = 1;
	return (NULL);
}
