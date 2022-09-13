/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:59:10 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/13 03:17:06 by abouchfa         ###   ########.fr       */
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
	pthread_mutex_unlock(&(data->print_mtx));
}

void	take_forks(t_philo *philo, t_data *data)
{
	int			i;
	t_fork_lst	*fork;

	i = -1;
	fork = *(data->forks);
	while (fork->id != philo->id)
		fork = fork->next;
	pthread_mutex_lock(&(fork->status));
	print_action(data, "has taken left fork 🍴", YELLOW, philo->id);
	pthread_mutex_lock(&(fork->next->status));
	print_action(data, "has taken right fork 🍴", YELLOW, philo->id);
}

void	release_forks(t_philo *philo, t_data *data)
{
	int			i;
	t_fork_lst	*fork;

	i = -1;
	fork = *(data->forks);
	while (fork->id != philo->id)
		fork = fork->next;
	pthread_mutex_unlock(&(fork->status));
	pthread_mutex_unlock(&(fork->next->status));
}

void	eat(t_philo *philo, t_data *data)
{
	take_forks(philo, data);
	print_action(data, "is eating 🍽", GREEN, philo->id);
	pthread_mutex_lock(&(philo->last_time_eat_mtx));
	philo->last_time_eat = get_current_time(data->start_time);
	pthread_mutex_unlock(&(philo->last_time_eat_mtx));
	pthread_mutex_lock(&(philo->is_eating_mtx));
	philo->is_eating = 1;
	pthread_mutex_unlock(&(philo->is_eating_mtx));
	my_usleep(data->time_to_eat);
	pthread_mutex_lock(&(philo->is_eating_mtx));
	philo->is_eating = 0;
	pthread_mutex_unlock(&(philo->is_eating_mtx));
	release_forks(philo, data);
}

int	check_dead(t_philo *philos, t_data *data)
{
	unsigned long	current_time;
	unsigned long	think_time;
	int				i;
	int				total;

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
		current_time = get_current_time(data->start_time);
		pthread_mutex_lock(&(philos[i].last_time_eat_mtx));
		think_time = current_time - philos[i].last_time_eat;
		pthread_mutex_unlock(&(philos[i].last_time_eat_mtx));
		pthread_mutex_lock(&(philos[i].is_eating_mtx));
		if (think_time >= data->time_to_die && !philos[i].is_eating)
		{
			pthread_mutex_lock(&(data->print_mtx));
			printf("%s%lu %i is dead 💀\n", RED, current_time, philos[i].id);
			return (1);
		}
		pthread_mutex_unlock(&(philos[i].is_eating_mtx));
		i++;
		i %= data->philos_nbr;
		usleep(100 * data->philos_nbr);
	}
	return (0);
}
