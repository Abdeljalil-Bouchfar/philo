/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeljalilbouchfar <abdeljalilbouchfar@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:59:10 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/08 22:33:20 by abdeljalilb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data *data, char *str, char *clr, int id)
{
	unsigned long	time;

	time = get_current_time(data->start_time);
	pthread_mutex_lock(&(data->print));
	printf("%s", clr);
	printf("%lu %i %s\n", time / 1000, id, str);
	printf("%s", RESET);
	pthread_mutex_unlock(&(data->print));
}

void	take_fork(t_philo *philo, t_data *data)
{
	int			i;
	t_fork_lst	*fork;

	i = -1;
	fork = *(data->forks);
	while (++i < data->philos_nbr)
	{
		pthread_mutex_lock(&(fork->status));
		if (fork->philo_id == -1)
		{
			if (philo->left_fork == NULL)
			{
				philo->left_fork = fork;
				fork->philo_id = philo->id;
				print_action(data, "has taken left fork", YELLOW, philo->id);
			}
			else if (philo->right_fork == NULL)
			{
				philo->right_fork = fork;
				fork->philo_id = philo->id;
				print_action(data, "has taken right fork", PURPLE, philo->id);
			}
			else
				break ;
		}
		pthread_mutex_unlock(&(fork->status));
		fork = fork->next;
	}
	pthread_mutex_unlock(&(fork->status));
}

void	eat(t_philo *philo, t_data *data)
{ 
	take_fork(philo, data);
	if (philo->left_fork != NULL && philo->right_fork != NULL
		&& !philo->is_eating)
	{
		philo->is_eating = 1;
		print_action(data, "is eating", GREEN, philo->id);
		philo->last_time_eat = get_current_time(data->start_time);
		my_usleep(data->time_to_eat);
	}
	if (philo->left_fork != NULL)
	{
		pthread_mutex_lock(&(philo->left_fork->status));
		philo->left_fork->philo_id = -1;
		pthread_mutex_unlock(&(philo->left_fork->status));
		philo->left_fork = NULL;
	}
	if (philo->right_fork != NULL)
	{
		pthread_mutex_lock(&(philo->right_fork->status));
		philo->right_fork->philo_id = -1;
		pthread_mutex_unlock(&(philo->right_fork->status));
		philo->right_fork = NULL;
	}
	philo->is_eating = 0;
}

void	check_dead(t_data *data)
{
	int	diff;
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
	{
		//printf("here %i\n", i);
		diff = get_current_time(data->start_time) - data->philos[i]->last_time_eat;
		if (diff >= data->time_to_die)
		{
			pthread_mutex_lock(&(data->print));
			print_action(data, "is dead", WHITE, i);
			return ;
		}
		if (i + 1 == data->philos_nbr)
			i = -1;
	}
}