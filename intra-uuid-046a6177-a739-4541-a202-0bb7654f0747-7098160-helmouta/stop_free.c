/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:56:37 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 10:45:35 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_data(t_data *data)
{
	unsigned int	i;

	if (!data)
		return (NULL);
	if (data->fork_mutex != NULL)
		free(data->fork_mutex);
	if (data->philos != NULL)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (data->philos[i] != NULL)
				free(data->philos[i]);
			i++;
		}
		free(data->philos);
	}
	free(data);
	return (NULL);
}

void	destroy_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		pthread_mutex_destroy(&data->philos[i]->meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

int	error_failure(char *str, t_data *data)
{
	if (data != NULL)
		free_data(data);
	return (ft_exit(str));
}

void	*error_null(char *str, t_data *data)
{
	if (data != NULL)
		free_data(data);
	ft_exit(str);
	return (NULL);
}
