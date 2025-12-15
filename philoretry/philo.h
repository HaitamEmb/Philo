/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:54:49 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 01:35:40 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHLIO_H

# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>


typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	FORK_LEFT = 4,
	FORK_RIGHT= 5
}	t_status;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	time_t			start_time;
	unsigned int		nb_philos;
	pthread_t		death_thread;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int			must_eat_count;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*fork_mutex;
	t_philo			**philos;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int		id;
	unsigned int		eating_times;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_mutex;
	time_t			last_meal;
	t_data			*data;
}	t_philo;

int			ft_atoi(char *str);
int			check_valid_args(int ac, char **av);
t_data			*init_data(int ac, char **av, int i);
void			*philo_routine(void *args);
long int		get_time(void);
void			ft_usleep(time_t time_in_ms, t_data *data);
void			routine_delay(time_t start_time);
void			write_status(t_philo *philo, bool reaper, t_status status);
void			*error_null(char *str, t_data *data);
void			*monitor_death(void *args);
int			routine_stopped(t_data *data);
int			error_failure(char *str, t_data *data);
void			*free_data(t_data *data);
void			destroy_mutexes(t_data *data);
int			ft_exit(char *str);

#endif