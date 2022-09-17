/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:05 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/17 10:19:44 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	supervisor(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (data->must_eat_nbr != -1)
		{
			pthread_mutex_lock(&(data->total_eat_mtx));
			if (data->total_eat >= data->philos_nbr)
				return (0);
			pthread_mutex_unlock(&(data->total_eat_mtx));
		}
		if (is_dead(philos[i], data))
			return (1);
		i++;
		i %= data->philos_nbr;
		usleep(50);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	int			eat_counter;

	philo = (t_philo *) arg;
	data = philo->data;
	eat_counter = 0;
	while (1)
	{
		eat(philo, data);
		eat_counter++;
		if (data->must_eat_nbr != -1)
		{
			pthread_mutex_lock(&(data->total_eat_mtx));
			if (eat_counter == data->must_eat_nbr)
				data->total_eat++;
			pthread_mutex_unlock(&(data->total_eat_mtx));
		}
		print_action(data, "is sleeping 😴", BLUE, philo->id);
		my_usleep(data->time_to_sleep);
		print_action(data, "is thinking 🤔", BLUE, philo->id);
	}
	pthread_detach(*(philo->thread));
	return (NULL);
}

void	init_data(int ac, char **av, t_data *data)
{
	data->start_time = get_current_time(0);
	data->philos_nbr = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->total_eat = 0;
	data->must_eat_nbr = -1;
	if (ac == 6)
		data->must_eat_nbr = ft_atoi(av[5]);
	pthread_mutex_init(&(data->print_mtx), NULL);
	pthread_mutex_init(&(data->total_eat_mtx), NULL);
}

t_philo	*set_data(int ac, char **av, t_data *data)
{
	t_philo	*philos;
	int		i;

	init_data(ac, av, data);
	philos = malloc(sizeof(t_philo) * (data->philos_nbr));
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->philos_nbr));
	i = -1;
	while (++i < data->philos_nbr)
	{
		philos[i].id = i + 1;
		philos[i].last_time_eat = 0;
		philos[i].thread = malloc(sizeof(pthread_t));
		philos[i].data = data;
		pthread_mutex_init(&(philos[i].last_time_eat_mtx), NULL);
		pthread_mutex_init(&(data->forks[i]), NULL);
	}
	return (philos);
}

int	main(int ac, char **av)
{
	int			i;
	t_data		*data;
	t_philo		*philos;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		if (validate_input(ac, av))
			return (1);
		philos = set_data(ac, av, data);
		i = -1;
		while (++i < data->philos_nbr)
		{
			pthread_create(philos[i].thread, NULL, routine, &philos[i]);
			usleep(60);
		}
		return (supervisor(philos, data));
	}
	if (ac < 5)
		ft_putstr_fd("Error: Too few arguments!\n", 2);
	else if (ac > 6)
		ft_putstr_fd("Error: Too many arguments!\n", 2);
	return (1);
}
