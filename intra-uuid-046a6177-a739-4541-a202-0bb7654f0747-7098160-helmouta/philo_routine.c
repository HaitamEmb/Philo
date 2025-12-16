/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:24:51 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 13:45:09 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	if (silent == true)
	{
		time_to_think = philo->data->time_to_eat / 2;
		if (time_to_think > 600)
			time_to_think = 200;
		ft_usleep(time_to_think, philo->data);
	}
	else
	{
		write_status(philo, false, THINKING);
		time_to_think = 0;
		if (philo->data->time_to_eat > philo->data->time_to_sleep)
			time_to_think = (philo->data->time_to_eat \
				- philo->data->time_to_sleep);
		if (philo->data->nb_philos % 2 == 1)
			time_to_think += philo->data->time_to_eat * 0.1;
		if (time_to_think > 0)
			ft_usleep(time_to_think + 1, philo->data);
	}
}

static void	eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex[philo->fork[0]]);
	write_status(philo, false, FORK_LEFT);
	pthread_mutex_lock(&philo->data->fork_mutex[philo->fork[1]]);
	write_status(philo, false, FORK_RIGHT);
	write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	if (routine_stopped(philo->data) == false)
	{
		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->eating_times += 1;
		pthread_mutex_unlock(&philo->meal_time_mutex);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->fork[0]]);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

static void	*one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex[philo->fork[0]]);
	write_status(philo, false, FORK_LEFT);
	ft_usleep(philo->data->time_to_die, philo->data);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->fork[0]]);
	return (NULL);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	routine_delay(philo->data->start_time);
	if (philo->data->time_to_die == 0)
		return (NULL);
	if (philo->data->nb_philos == 1)
		return (one_philo_case(philo));
	else if (philo->data->nb_philos % 2 == 1 \
		&& philo->id == philo->data->nb_philos - 1)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	else if (philo->id % 2)
		think(philo, true);
	while (routine_stopped(philo->data) == false)
	{
		eat_sleep(philo);
		think(philo, false);
	}
	return (NULL);
}
