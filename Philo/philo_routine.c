#include "philo.h"

void print_status(t_philo *philo, char *status)
{
	long int	timestamp;

	pthread_mutex_lock(&philo->args.print_mutex);
	timestamp = get_time() - philo->args->start_time;
	if (!monitor_death(philo, 0) && timestamp >= 0 && timestamp <= 2147483647)
		printf("%ld %d %s\n", timestamp, philo->id, status);
	//pthread_mutex_unlock(&philo->args->print_mutex);
}


void sleep_think(t_philo *philo)
{
	print_status(philo, "is sleeping\n");
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args.time_to_sleep);
	print_status(philo, "is thinking\n");
	pthread_mutex_unlock(&philo->args->print_mutex);
}


void	*philo_routine(t_philo *philo)
{
	
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "has taken a fork\n");
	pthread_mutex_unlock(&philo->args->print_mutex);
	if (!philo->right_fork)
	{
		ft_usleep(philo->args.time_to_die * 2);
		pthread_mutex_unlock(&philo->left_fork);
		return (NULL);
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork\n");
	pthread_mutex_unlock(&philo->args->print_mutex);
	print_status(philo, "is eating\n");
	pthread_mutex_lock(&philo->args->time_eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->args.time_eat);
	pthred_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args.time_to_eat);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	sleep_think(philo);
}