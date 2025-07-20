/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:49:35 by romukena          #+#    #+#             */
/*   Updated: 2025/07/14 23:44:36 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	swap(t_mylist **stack, char *name)
{
	t_mylist	*current;
	int			temp;

	current = *stack;
	if (!stack || !*stack || (*stack)->next == NULL)
		return ;
	temp = current->value;
	current->value = current->next->value;
	current->next->value = temp;
	if (name)
	{
		write(1, name, ft_strlen(name));
		write(1, "\n", 1);
	}
}

void	push(t_mylist **stack_a, t_mylist **stack_b, char *name)
{
	t_mylist	*node;

	if (!stack_a || !stack_b || !*stack_a)
		return ;
	node = *stack_a;
	*stack_a = (*stack_a)->next;
	node->next = *stack_b;
	*stack_b = node;
	if (name)
	{
		write(1, name, ft_strlen(name));
		write(1, "\n", 1);
	}
}

void	rotate(t_mylist **stack, char *name)
{
	t_mylist	*tmp;
	t_mylist	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	*stack = tmp->next;
	tmp->next = NULL;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = tmp;
	if (name)
	{
		write(1, name, ft_strlen(name));
		write(1, "\n", 1);
	}
}

void	reverse_rotate(t_mylist **stack, char *name)
{
	t_mylist	*prev;
	t_mylist	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	prev = NULL;
	last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
	if (name)
	{
		write(1, name, ft_strlen(name));
		write(1, "\n", 1);
	}
}
