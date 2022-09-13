/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:59:10 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/13 22:57:35 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data *data, char *str, char *clr, int id)
{
	unsigned long	time;

	time = get_current_time(data->start_time);
	pthread_mutex_lock(&(data->print_mtx));
	printf("%s", clr);
	printf("%lu %i %s\n", time, id, str);
	printf("%s", RESET);
	if (ft_strcmp("is dead 💀", str) != 0)
		pthread_mutex_unlock(&(data->print_mtx));
}

void	take_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_t	*forks;

	forks = data->forks;
	pthread_mutex_lock(&(forks[philo->id - 1]));
	print_action(data, "has taken left fork 🍴", YELLOW, philo->id);
	pthread_mutex_lock(&(forks[philo->id % data->philos_nbr]));
	print_action(data, "has taken right fork 🍴", YELLOW, philo->id);
}

void	release_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_t	*forks;

	forks = data->forks;
	pthread_mutex_unlock(&(forks[philo->id - 1]));
	pthread_mutex_unlock(&(forks[philo->id % data->philos_nbr]));
}

void	eat(t_philo *philo, t_data *data)
{
	take_forks(philo, data);
	print_action(data, "is eating 🍽", GREEN, philo->id);
	pthread_mutex_lock(&(philo->last_time_eat_mtx));
	philo->last_time_eat = get_current_time(data->start_time);
	pthread_mutex_unlock(&(philo->last_time_eat_mtx));
	my_usleep(data->time_to_eat);
	release_forks(philo, data);
}

int	is_dead(t_philo philo, t_data *data)
{
	unsigned long	current_time;
	unsigned long	think_time;

	current_time = get_current_time(data->start_time);
	pthread_mutex_lock(&(philo.last_time_eat_mtx));
	think_time = current_time - philo.last_time_eat;
	pthread_mutex_unlock(&(philo.last_time_eat_mtx));
	if (think_time >= data->time_to_die)
	{
		print_action(data, "is dead 💀", RED, philo.id);
		return (1);
	}
	return (0);
}
