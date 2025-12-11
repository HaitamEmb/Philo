/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:44:15 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/11 17:18:54 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (0);
	data->args.num_philo = ft_atoi(av[1]);
	data->args.time_to_die = ft_atoi(av[2]);
	data->args.time_to_eat = ft_atoi(av[3]);
	data->args.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->args.num_must_eat = ft_atoi(av[5]);
	else
		data->args.num_must_eat = -1;
	if (data->args.num_philo <= 0 || data->args.time_to_die < 0
		|| data->args.time_to_eat < 0 || data->args.time_to_sleep < 0
		|| (ac == 6 && data->args.num_must_eat <= 0))
		return (0);
	return (1);
}

void	mutex_init(t_data *data)
{
	pthread_mutex_init(&data->args.print_mutex, NULL);
	pthread_mutex_init(&data->args.death_mutex, NULL);
	pthread_mutex_init(&data->args.time_eat, NULL);
	pthread_mutex_init(&data->args.finished_mutex, NULL);
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	data->args.start_time = get_time();
	data->args.stop = 0;
	data->args.finished_count = 0;
	mutex_init(data);
	while (i < data->args.num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->args.start_time;
		data->philos[i].is_fnished = 0;
		data->philos[i].right_fork = NULL;
		pthread_mutex_init(&data->philos[i].left_fork, NULL);
		if (data->args.num_philo == 1)
			return (1);
		if (i == data->args.num_philo - 1)
			data->philos[i].right_fork = &data->philos[0].left_fork;
		else
			data->philos[i].right_fork = &data->philos[i + 1].left_fork;
		i++;
	}
	return (1);
}
