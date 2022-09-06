/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                    		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:22:42 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/06 09:28:41 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_alloc_lst	*ft_lstnew(void *content)
{
	t_alloc_lst	*list;

	list = malloc(sizeof(t_alloc_lst));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

static void	ft_lstadd_front(t_alloc_lst	**lst, t_alloc_lst	*new)
{
	if (!new)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

void	ft_lstclear(t_alloc_lst **lst)
{
	t_alloc_lst	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if (*lst && (*lst)->content)
			free((*lst)->content);
		if (*lst)
			free(*lst);
		(*lst) = temp;
	}
}

void	*alloc(size_t size, t_data *data)
{
	void	*content;

	content = malloc(size);
	if (!content)
	{
		perror("");
		exit(errno);
	}
	ft_lstadd_front(data->alloc_list, ft_lstnew(content));
	return (content);
}
