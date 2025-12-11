/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:45:17 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/11 18:54:44 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	time;
	long int		ms_time;

	gettimeofday(&time, NULL);
	ms_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms_time);
}

int	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(100);
	return (0);
}

int	monitor_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->args->death_mutex);
	if (i)
		philo->args->stop = i;
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&philo->args->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->death_mutex);
	return (0);
}

int	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}