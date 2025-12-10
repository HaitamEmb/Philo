#include "philo.h"



void	*is_dead(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->args->time_to_die + 1);
	pthread_mutex_lock(&philo->args->time_to_eat);
	pthread_mutex_lock(&philo->args->finished_coun);
	if (!monitor_death(philo, 0) && !philo->is_fnished
		&& (get_time() - philo->last_meal) >= (long int)philo->args.time_to_die)
	{
		pthread_mutex_unlock(&philo->args->time_eat);
		pthread_mutex_unlock(&philo->args->finished_mutex);
		print_status(philo, "died\n");
		monitor_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->args->time_eat);
	pthread_mutex_unlock(&philo->args->finished_mutex);
	return (NULL);
}




void *thread(void *arg)
{
    t_philo	*philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
	ft_usleep(philo->args.time_to_eat / 10);
    while (!monitor_death(philo, 0))
    {
	pthread_create(&philo->death_thread_id, NULL, is_dead, arg);
	philo_routine(philo);
	pthread_detach(philo->death_thread_id);
	if ((int)++philo->meals_eaten == philo->args.num_must_eat)
	{
		pthread_mutex_lock(&philo->args->finished_mutex);
		philo->is_fnished = 1;
		philo->args->finished_count++;
		if (philo->args->finished_count == philo->args.num_philo)
		{
			pthread_mutex_unlock(&philo->args->finished_mutex);
			monitor_death(philo, 2);
		}
		pthread_mutex_unlock(&philo->args->finished_mutex);
		return (NULL);
	}
    }
    return (NULL);
}


int threading(t_data *data)
{
	int i;

	i = 0;
	while (i < data->args.num_philo)
	{
		data->philos[i].args = &data->args;
		if (pthread_create(&data->philos[i].thread_id, NULL, thread, &data->philos[i]) != 0)
			return (ft_exit("Error creating threads\n"));
		i++;
	}
	return (1);
}