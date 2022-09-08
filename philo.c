/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeljalilbouchfar <abdeljalilbouchfar@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:05 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/08 22:19:58 by abdeljalilb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int			i;
	t_data		*data;
	t_philo		*philo;

	i = -1;
	data = (t_data *) arg;
	philo = data->philos[data->i];
	while (data->min_eat)
	{
		eat(philo, data);
		print_action(data, "is sleeping", BLUE, philo->id);
		my_usleep(data->time_to_sleep);
		print_action(data, "is thinking", RED, philo->id);
		if (philo->min_eat != -1)
			philo->min_eat--;
	}
	return (NULL);
}

void	set_data(t_data *data)
{
	int	i;

	i = -1;
	data->philos = alloc(sizeof(t_philo *) * (data->philos_nbr + 1), data);
	data->forks = alloc(sizeof(t_fork_lst *), data);
	*(data->forks) = NULL;
	while (++i < data->philos_nbr)
	{
		data->philos[i] = alloc(sizeof(t_philo), data);
		data->philos[i]->id = i + 1;
		data->philos[i]->is_eating = 0;
		data->philos[i]->last_time_eat = 0;
		data->philos[i]->min_eat = data->min_eat;
		data->philos[i]->left_fork = NULL;
		data->philos[i]->right_fork = NULL;
		insert_frok_lst(data->forks, i + 1);
	}
	data->philos[i] = alloc(sizeof(t_philo), data);
	data->philos[i] = NULL;
	pthread_mutex_init(&(data->print), NULL);
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
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	data->min_eat = -1;
	if (ac == 6)
		data->min_eat = ft_atoi(av[5]);
}

int	main(int ac, char **av)
{
	int			i;
	t_data		data;
	pthread_t	*threads;

	if (ac < 5)
		print_error("Error: Too few arguments!\n");
	else if (ac > 6)
		print_error("Error: Too many arguments!\n");
	data.alloc_list = malloc(sizeof(t_alloc_lst *));
	*(data.alloc_list) = NULL;
	parse_input(ac, av, &data);
	set_data(&data);
	i = -1;
	threads = alloc(sizeof(pthread_t) * data.philos_nbr, &data);
	while (++i < data.philos_nbr)
	{
		data.i = i;
		if (pthread_create(&threads[i], NULL, routine, &data) != 0)
			exit(1);
		//pthread_detach(threads[i]);
	}
	i = -1;
	// while (++i < data.philos_nbr)
	// 	pthread_join(threads[i], NULL);
	// ft_lstclear(data.alloc_list);
	check_dead(&data);
}
