/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:27:26 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/08 03:16:07 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../philo.h"

static t_fork_lst	*ft_lstnew_fork(int id)
{
	t_fork_lst	*new;

	new = malloc(sizeof(t_fork_lst));
	if (!new)
		return (NULL);
	new->id = id;
	new->philo_id = -1;
	new->next = NULL;
	pthread_mutex_init(&(new->status), NULL);
	return (new);
}

void	insert_frok_lst(t_fork_lst	**head, int id)
{
	t_fork_lst	*new;
	t_fork_lst	*temp;

	new = ft_lstnew_fork(id);
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
