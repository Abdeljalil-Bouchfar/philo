/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:34:49 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/13 23:10:49 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_current_time(unsigned long st_time)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) == -1)
		ft_putstr_fd("System call error\n", 2);
	return (((tp.tv_sec * 1000) + tp.tv_usec / 1000) - st_time);
}

void	my_usleep(unsigned long mili_sec)
{
	unsigned long	start;

	start = get_current_time(0);
	while (get_current_time(start) < mili_sec)
		usleep(100);
}
