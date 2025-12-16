/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:39:32 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 10:45:34 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time() - philo->data->start_time,
		philo->id + 1, str);
}

void	write_status(t_philo *philo, bool reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (routine_stopped(philo->data) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == FORK_LEFT || status == FORK_RIGHT)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->write_mutex);
}
