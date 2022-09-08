/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeljalilbouchfar <abdeljalilbouchfar@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:57:03 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/08 22:16:04 by abdeljalilb      ###   ########.fr       */
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
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/*
	All time in the program is with microseconds
	
	Philo Status:
		0: Nothing
		1: Eeating
		2: Sleeping
		3: Thinking
	
	Fork Status:
		0: On the taple
		1: Taken

	When a philosopher has finished eating, they put their forks back
	on the table and start sleeping. Once awake, they start thinking again.
	The simulation stops when a philosopher dies of starvation.
	
	No need to say that philosophers should avoid dying!
*/

typedef struct s_fork_lst
{
	int					id;
	int					philo_id;
	struct s_fork_lst	*next;
	pthread_mutex_t		status;
}	t_fork_lst;

typedef struct s_philo
{
	int				id;
	unsigned long	last_time_eat;
	int				is_eating;
	int				min_eat;
	t_fork_lst		*left_fork;
	t_fork_lst		*right_fork;
}	t_philo;

typedef struct s_alloc_lst
{
	void				*content;
	struct s_alloc_lst	*next;
}	t_alloc_lst;

typedef struct s_data
{
	int 			i;
	long long		start_time;
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat;
	t_philo			**philos;
	t_fork_lst		**forks;
	t_alloc_lst		**alloc_list;
	pthread_mutex_t	print;
}	t_data;

//------------------ Time Functins ------------------

unsigned long	get_current_time(unsigned long st_time);
void			my_usleep(int mcrs);

//--------------------- Utils -----------------------
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			print_error(char *error);
void			*alloc(size_t size, t_data *data);
void			ft_lstclear(t_alloc_lst **lst);

void			insert_frok_lst(t_fork_lst	**head, int id);

//--
void			eat(t_philo *philo, t_data *data);
void			check_dead(t_data *data);
void			print_action(t_data *data, char *str, char *clr, int id);

#endif