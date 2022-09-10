/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:57:03 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/11 00:32:24 by abouchfa         ###   ########.fr       */
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

typedef struct s_fork_lst
{
	int					id;
	struct s_fork_lst	*next;
	pthread_mutex_t		status;
}	t_fork_lst;

typedef struct s_data
{
	int				must_eat_nbr;
	int				philos_nbr;
	unsigned long	start_time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	t_fork_lst		**forks;
	pthread_mutex_t	print_mtx;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_counter;
	unsigned long	last_time_eat;
	int				is_eating;
	pthread_t		*thread;
	t_data			*data;
	pthread_mutex_t	eat_counter_mtx;
	pthread_mutex_t	is_eating_mtx;
	pthread_mutex_t	last_time_eat_mtx;
}	t_philo;

//------------------ Time Functins ------------------

unsigned long	get_current_time(unsigned long st_time);
void			my_usleep(unsigned long mili_sec);

//--------------------- Utils -----------------------
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putstr_fd(char *s, int fd);
void			print_error(char *error);
void			insert_frok_lst(t_fork_lst	**head, int id);

//--
void			eat(t_philo *philo, t_data *data);
void			check_dead(t_philo *philos, t_data *data);
void			print_action(t_data *data, char *str, char *clr, int id);

#endif