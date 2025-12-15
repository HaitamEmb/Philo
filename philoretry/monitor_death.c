/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:42:32 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 01:32:48 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	stop_routine(t_data *data, bool state)
{
	pthread_mutex_lock(&data->stop_mutex);
		data->stop = state;
	pthread_mutex_unlock(&data->stop_mutex);
}

int	routine_stopped(t_data *data)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop == true)
		result = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (result);
}

static int	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->data->time_to_die)
	{
		stop_routine(philo->data, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_mutex);
		return (1);
	}
	return (0);
}


static int	ended(t_data *data)
{
	unsigned int	i;
	int		philos_ate;

	philos_ate = 1;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i]->meal_time_mutex);
		if (kill_philo(data->philos[i]))
			return (1);
		if (data->must_eat_count != -1)
			if (data->philos[i]->eating_times
				< (unsigned int)data->must_eat_count)
				philos_ate = 0;
		pthread_mutex_unlock(&data->philos[i]->meal_time_mutex);
		i++;
	}
	if (data->must_eat_count != -1 && philos_ate == 1)
	{
		stop_routine(data, true);
		return (1);
	}
	return (0);
}

void	*monitor_death(void *args)
{
	t_data			*data;

	data = (t_data *)args;
	if (data->must_eat_count == 0)
		return (NULL);
	stop_routine(data, false);
	routine_delay(data->start_time);
	while (true)
	{
		if (ended(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}