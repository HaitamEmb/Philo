#ifndef	PHILO_H
# define PHILO_H


#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>	
#include <sys/time.h>
#include <stdio.h>


typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	long int			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_eat;
	pthread_mutex_t	finished_mutex;
	int				stop;
	int				finished_count;
}	t_args;

typedef struct s_philo
{
	int		id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	long int	last_meal;
	unsigned int	meals_eaten;
	pthread_t	thread_id;
	pthread_t	death_thread_id;
	t_args	*args;
	int		is_fnished;
}	t_philo;

typedef struct s_data
{
	t_args		args;
	t_philo		*philos;
}	t_data;

int		parse_args(int ac, char **av, t_data *data);
int		init(t_data *data);
long int	get_time(void);
void	ft_putstr_fd(char *s, int fd);
void	*philo_routine(t_philo *philo);
int	ft_strlen(char *str);
void	*monitor_death(t_philo *philo, int i);
void	print_status(t_philo *philo, char *status);
int	ft_usleep(long int time_in_ms);
int	threading(t_data *philo);
int	ft_exit(char *str);
int	ft_atoi(const char *str);
int check_arg_numeric(char *av);
int check_valid_args(int ac, char **av);
void	stop_and_free(t_data *data);
#endif