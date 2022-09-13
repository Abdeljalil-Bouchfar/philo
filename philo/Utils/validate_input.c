/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:15:54 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/13 23:17:54 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	validate_input(int ac, char **av)
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
			ft_putstr_fd(": invalid argument\n", 2);
			return (1);
		}
	}
	return (0);
}
