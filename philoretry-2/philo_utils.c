/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmouta <helmouta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:00:39 by helmouta          #+#    #+#             */
/*   Updated: 2025/12/16 10:45:33 by helmouta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

int	check_arg_numeric(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0)
	{
		while (s && *s)
		{
			write(fd, &*s, 1);
			s++;
		}
	}
}

int	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

int	check_valid_args(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0 \
	|| check_arg_numeric(av[1]) == 0)
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
			return (ft_exit("Invalid times each philosopher must eat\n"));
	}
	return (1);
}
