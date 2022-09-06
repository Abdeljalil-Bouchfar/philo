/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:05 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/06 11:59:29 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int			i;
	t_data		*data;

	i = -1;
	data = (t_data *) arg;
	return (NULL);
}

void	set_data(t_data *data)
{
	int	i;

	i = -1;
	data->philos = alloc(sizeof(t_philo *) * (data->philos_nbr + 1), data);
	data->forks = alloc(sizeof(t_fork_lst *), data);
	*(data->forks) = NULL;
	while (++i < data->philos_nbr * 2)
	{
		if (i <= data->philos_nbr)
		{
			data->philos[i] = alloc(sizeof(t_philo), data);
			if (i == data->philos_nbr)
				data->philos[i] = NULL;
			else
			{
				data->philos[i]->id = i + 1;
				data->philos[i]->left_fork = -1;
				data->philos[i]->right_fork = -1;
				data->philos[i]->status = -1;
			}
		}
		insert_frok_lst(data->forks, i + 1, -1);
	}
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
	data->start_time = get_current_time();
	data->philos_nbr = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->philo_meat_nbr = ft_atoi(av[5]);
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
		if (pthread_create(&threads[i], NULL, routine, &data) != 0)
			exit(1);
	}
	i = -1;
	while (++i < data.philos_nbr)
		pthread_join(threads[i], NULL);
	printf("%lld\n", data.start_time);
	ft_lstclear(data.alloc_list);
}
