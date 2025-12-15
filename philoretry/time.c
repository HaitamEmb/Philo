/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:44:36 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 00:21:09 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;
	time_t		ms_time;

	gettimeofday(&time, NULL);
	ms_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms_time);
}

void	routine_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue;
}

void	ft_usleep(time_t time_in_ms, t_data *data)
{
	time_t	start_time;

	start_time = get_time() + time_in_ms;
	while (get_time() < start_time)
	{
		if (routine_stopped(data) == true)
			break ;
		usleep(100);
	}
}