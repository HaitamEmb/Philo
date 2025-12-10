#include "philo.h"

int check_arg_numeric(char *av)
{
	int i;

	i = 0;
	while(av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int check_valid_args(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0 || check_arg_numeric(av[1]) == 0)
		return (ft_exit("Invalid number of philosophers\n"));
	if (ft_atoi(av[2]) <= 0 || check_arg_numeric(av[2]) == 0)
		return (ft_exit("Invalid time to die\n"));
	if (ft_atoi(av[3]) <= 0 || check_arg_numeric(av[3]) == 0)
		return (ft_exit("Invalid time to eat\n"));
	if (ft_atoi(av[4]) <= 0 || check_arg_numeric(av[4]) == 0)
		return (ft_exit("Invalid time to sleep\n"));
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 0 || check_arg_numeric(av[5]) == 0)
			return (ft_exit("Invalid number of times each philosopher must eat\n"));
	}
	return (0);
}

void	stop_and_free(t_data *data)
{
	int	i;

	i = -1;
	while (!monitor_death(&data->philos[0], 0)) //to check
		ft_usleep(1);
	while (++i < data->args.num_philo)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_mutex_destroy(&data->args.print_mutex);
	i = -1;
	while (++i < data->args.num_philo)
		pthread_mutex_destroy(&data->philos[i].left_fork);
	if(data->args.stop == 2)
		ft_putstr_fd("All philosophers have finished eating.\n", 1);
	free(data->philos);
}

int	main(int ac , char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (ft_exit("Invalid number of arguments\n"));
	if (!(check_valid_args(ac, av)))
		return (0);
	data.philos = malloc(sizeof(t_philo) * data.args.num_philo);
	if (!(data.philos))
		return (ft_exit("Malloc error\n"));
	if (!(init(&data)) || !(threading(&data)))
	{
		free(data.philos);
		return (ft_exit("Error during initialization or threading\n"));
	}
	stop_and_free(&data);
}