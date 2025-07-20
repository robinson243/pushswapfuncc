/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:49:26 by romukena          #+#    #+#             */
/*   Updated: 2025/07/20 01:24:17 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	free_list(t_mylist **lst)
{
	t_mylist	*current;
	t_mylist	*data_next;

	current = *lst;
	if (!lst || !*lst)
		return ;
	if (!lst)
		return ;
	while (current)
	{
		data_next = current->next;
		free(current);
		current = data_next;
	}
	*lst = NULL;
}

t_mylist	*createnode(int value, int index_count)
{
	t_mylist	*node;

	node = malloc(sizeof(t_mylist));
	node->value = value;
	node->index = index_count;
	node->next = NULL;
	return (node);
}

void	addback(t_mylist **List, int value)
{
	t_mylist	*node;
	t_mylist	*current;

	current = *List;
	node = createnode(value, 0);
	if (*List == NULL)
	{
		*List = node;
		node->next = NULL;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = node;
	node->next = NULL;
}

void	add_front(t_mylist **lst, t_mylist *new)
{
	new->next = *lst;
	*lst = new;
}

int	countlist(t_mylist *head)
{
	t_mylist	*current;
	int			i;

	current = head;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}