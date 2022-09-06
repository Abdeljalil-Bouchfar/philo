/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:57:03 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/06 11:51:48 by abouchfa         ###   ########.fr       */
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

/*
	All time in the program is with microseconds




*/

typedef struct s_philo
{
	int	id;
	int	left_fork;
	int	right_fork;
	int	status;
}	t_philo;

typedef struct s_fork_lst
{
	int					id;
	int					philo_id;
	struct s_fork_lst	*next;
	struct s_fork_lst	*head;
}	t_fork_lst;

typedef struct s_alloc_lst
{
	void				*content;
	struct s_alloc_lst	*next;
}	t_alloc_lst;

typedef struct s_data
{
	long long		start_time;
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_meat_nbr;
	t_philo			**philos;
	t_fork_lst		**forks;
	t_alloc_lst		**alloc_list;
}	t_data;

//------------------ Time Functins ------------------

long long	get_current_time(void);
void		my_usleep(int mcrs);

//--------------------- Utils -----------------------
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		print_error(char *error);
void		*alloc(size_t size, t_data *data);
void		ft_lstclear(t_alloc_lst **lst);

void		insert_frok_lst(t_fork_lst	**head, int id, int philo_id);

#endif