/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:57:03 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/17 10:03:48 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

typedef struct s_data
{
	int				must_eat_nbr;
	int				philos_nbr;
	int				total_eat;
	unsigned long	start_time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	total_eat_mtx;
}	t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	last_time_eat;
	pthread_t		*thread;
	t_data			*data;
	pthread_mutex_t	last_time_eat_mtx;
}	t_philo;

//------------------ Time Functins -------------------

unsigned long	get_current_time(unsigned long st_time);
void			my_usleep(unsigned long mili_sec);

//--------------------- Utils ------------------------
int				validate_input(int ac, char **av);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putstr_fd(char *s, int fd);

//--------------------- Routine ----------------------
void			eat(t_philo *philo, t_data *data);
int				is_dead(t_philo philo, t_data *data);
void			print_action(t_data *data, char *str, char *clr, int id);

#endif