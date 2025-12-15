/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:01:30 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 01:39:41 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threading(t_data *data)
{
	unsigned int	i;

	data->start_time = get_time() + (data->nb_philos * 2 * 10);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&philo_routine, data->philos[i]) != 0)
			return (error_failure("Error creating thread\n", data));
		i++;
	}
	if (data->nb_philos > 1)
	{
		if (pthread_create(&data->death_thread, NULL,
				&monitor_death, data) != 0)
			return (error_failure("Error creating thread\n", data));
	}
	return (1);
}

static void	stop_and_free(t_data	*data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->nb_philos > 1)
		pthread_join(data->death_thread, NULL);
	destroy_mutexes(data);
	free_data(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (ft_exit("Invalid numbers of arguments\n"));
	if (!check_valid_args(ac, av))
		return (0);
	data = init_data(ac, av, 1);
	if (!data)
		return (ft_exit("Initialization failed\n"));
	if (!start_threading(data))
		return (ft_exit("Simulation failed to start\n"));
	stop_and_free(data);
	return (0);
}
