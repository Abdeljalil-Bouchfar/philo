/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:05 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/13 03:23:09 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	//pthread_detach(*(philo->thread));
	return (NULL);
}

t_philo	*set_data(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * (data->philos_nbr));
	data->forks = malloc(sizeof(t_fork_lst *));
	*(data->forks) = NULL;
	i = -1;
	while (++i < data->philos_nbr)
	{
		philos[i].id = i + 1;
		philos[i].eat_counter = 0;
		philos[i].is_eating = 0;
		philos[i].last_time_eat = 0;
		philos[i].thread = malloc(sizeof(pthread_t));
		philos[i].data = data;
		pthread_mutex_init(&(philos[i].last_time_eat_mtx), NULL);
		pthread_mutex_init(&(philos[i].eat_counter_mtx), NULL);
		pthread_mutex_init(&(philos[i].is_eating_mtx), NULL);
		insert_frok_lst(data->forks, i + 1);
	}
	return (philos);
}

void	parse_input(int ac, char **av, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i] && av[i][j] >= '0' && av[i][j] <= '9')
			j++;
		if (ft_atoi(av[i]) == 0 || av[i][j])
		{
			ft_putstr_fd(av[i], 2);
			print_error(": invalid argument\n");
		}
	}
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

int	main(int ac, char **av)
{
	int			i;
	t_data		data;
	t_philo		*philos;

	if (ac < 5)
		print_error("Error: Too few arguments!\n");
	else if (ac > 6)
		print_error("Error: Too many arguments!\n");
	parse_input(ac, av, &data);
	philos = set_data(&data);
	i = -1;
	while (++i < data.philos_nbr)
		if (i % 2 == 0)
			pthread_create(philos[i].thread, NULL, routine, &philos[i]);
	usleep(100 * data.philos_nbr);
	i = -1;
	while (++i < data.philos_nbr)
		if (i % 2 != 0)
			pthread_create(philos[i].thread, NULL, routine, &philos[i]);
	// while (++i < data.philos_nbr)
	// 	pthread_join(*(philos[i].thread), NULL);
	return (check_dead(philos, &data));
}
