/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:10:37 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 10:41:58 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!forks)
		return (error_null("malloc failed \n", 0));
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null("mutex init failed \n", 0));
		i++;
	}
	return (forks);
}

static void	philos_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->data->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->nb_philos;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philos(t_data *data)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (error_null("malloc failed\n", 0));
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (error_null("malloc failed\n", 0));
		if (pthread_mutex_init(&philos[i]->meal_time_mutex, 0) != 0)
			return (error_null("malloc failed\n", 0));
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->eating_times = 0;
		philos_forks(philos[i]);
		i++;
	}
	return (philos);
}

static int	init_mutexes(t_data *data)
{
	data->fork_mutex = init_forks(data);
	if (!data->fork_mutex)
		return (0);
	if (pthread_mutex_init(&data->stop_mutex, 0) != 0)
		return (error_failure("stop mutex init failed \n", data));
	if (pthread_mutex_init(&data->write_mutex, 0) != 0)
		return (error_failure("write_mutex init failed \n", data));
	return (1);
}

t_data	*init_data(int ac, char **av, int i)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (error_null("malloc failed\n", 0));
	data->nb_philos = ft_atoi(av[i++]);
	data->time_to_die = ft_atoi(av[i++]);
	data->time_to_eat = ft_atoi(av[i++]);
	data->time_to_sleep = ft_atoi(av[i++]);
	data->must_eat_count = -1;
	if (ac - 1 == 5)
		data->must_eat_count = ft_atoi(av[i]);
	data->philos = init_philos(data);
	if (!data->philos)
		return (NULL);
	if (!init_mutexes(data))
		return (NULL);
	data->stop = false;
	return (data);
}
