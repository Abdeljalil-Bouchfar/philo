/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:27:26 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/06 11:47:55 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../philo.h"

static t_fork_lst	*ft_lstnew_fork(int id, int philo_id)
{
	t_fork_lst	*new;

	new = malloc(sizeof(t_fork_lst));
	if (!new)
		return (NULL);
	new->id = id;
	new->philo_id = philo_id;
	new->next = NULL;
	return (new);
}

void	insert_frok_lst(t_fork_lst	**head, int id, int philo_id)
{
	t_fork_lst	*new;
	t_fork_lst	*temp;

	new = ft_lstnew_fork(id, philo_id);
	if (!new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		(*head)->next = new;
	}
	else
	{
		temp = (*head)->next;
		while (temp->next != *head)
			temp = temp->next;
		new->next = *head;
		*head = new;
		temp->next = new;
	}
}
