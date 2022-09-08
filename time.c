/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeljalilbouchfar <abdeljalilbouchfar@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:34:49 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/08 21:59:48 by abdeljalilb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(int mcrs)
{
	while (mcrs > 100)
	{
		usleep(100);
		mcrs -= 100;
	}
	usleep(mcrs);
}

unsigned long	get_current_time(unsigned long st_time)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) == -1)
		print_error("System call error\n");
	return (((tp.tv_sec * 1000000) + tp.tv_usec) - st_time);
}
