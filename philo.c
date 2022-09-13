/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:05 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/13 23:20:21 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	supervisor(t_philo *philos, t_data *data)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (1)
	{
		if (total == data->philos_nbr)
			return (1);
		pthread_mutex_lock(&(philos[i].eat_counter_mtx));
		if (philos[i].eat_counter == data->must_eat_nbr)
			total++;
		pthread_mutex_unlock(&(philos[i].eat_counter_mtx));
		if (is_dead(philos[i], data))
			return (1);
		i++;
		i %= data->philos_nbr;
		usleep(100 * data->philos_nbr);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *) arg;
	data = philo->data;
	while (philo->eat_counter < data->must_eat_nbr || data->must_eat_nbr == -1)
	{
		eat(philo, data);
		print_action(data, "is sleeping 😴", BLUE, philo->id);
		my_usleep(data->time_to_sleep);
		print_action(data, "is thinking 🤔", BLUE, philo->id);
		if (data->must_eat_nbr != -1)
		{
			pthread_mutex_lock(&(philo->eat_counter_mtx));
			philo->eat_counter++;
			pthread_mutex_unlock(&(philo->eat_counter_mtx));
		}
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
	data->must_eat_nbr = -1;
	if (ac == 6)
		data->must_eat_nbr = ft_atoi(av[5]);
	pthread_mutex_init(&(data->print_mtx), NULL);
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
		philos[i].eat_counter = 0;
		philos[i].last_time_eat = 0;
		philos[i].thread = malloc(sizeof(pthread_t));
		philos[i].data = data;
		pthread_mutex_init(&(philos[i].last_time_eat_mtx), NULL);
		pthread_mutex_init(&(philos[i].eat_counter_mtx), NULL);
		pthread_mutex_init(&(data->forks[i]), NULL);
	}
	return (philos);
}

int	main(int ac, char **av)
{
	int			i;
	t_data		*data;
	t_philo		*philos;

	if (ac < 5)
		ft_putstr_fd("Error: Too few arguments!\n", 2);
	else if (ac > 6)
		ft_putstr_fd("Error: Too many arguments!\n", 2);
	data = malloc(sizeof(t_data));
	if (validate_input(ac, av))
		return (1);
	philos = set_data(ac, av, data);
	i = -1;
	while (++i < data->philos_nbr)
		if (i % 2 == 0)
			pthread_create(philos[i].thread, NULL, routine, &philos[i]);
	usleep(100 * data->philos_nbr);
	i = -1;
	while (++i < data->philos_nbr)
		if (i % 2 != 0)
			pthread_create(philos[i].thread, NULL, routine, &philos[i]);
	return (supervisor(philos, data));
}
