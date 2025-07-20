/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:13:02 by romukena          #+#    #+#             */
/*   Updated: 2025/07/19 22:16:47 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	sort_two(t_mylist **stack)
{
	if ((*stack)->value > (*stack)->next->value)
		swap(stack, "sa");
	else
		return ;
}

void	sort_three(t_mylist **stack)
{
	if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
		return ;
	if ((*stack)->value > (*stack)->next->value
		&& (*stack)->next->value < (*stack)->next->next->value
		&& (*stack)->value < (*stack)->next->next->value)
		swap(stack, "sa");
	else if ((*stack)->value > (*stack)->next->value
		&& (*stack)->next->value < (*stack)->next->next->value)
		rotate(stack, "ra");
	else if ((*stack)->value > (*stack)->next->value
		&& (*stack)->next->value > (*stack)->next->next->value)
	{
		rotate(stack, "ra");
		swap(stack, "sa");
	}
	else if ((*stack)->value < (*stack)->next->value
		&& (*stack)->next->value > (*stack)->next->next->value
		&& (*stack)->value < (*stack)->next->next->value)
	{
		reverse_rotate(stack, "rra");
		swap(stack, "sa");
	}
	else if ((*stack)->value < (*stack)->next->value
		&& (*stack)->next->value > (*stack)->next->next->value)
		reverse_rotate(stack, "rra");
}

int	find_smallest(t_mylist **stack_a)
{
	t_mylist	*cur;
	int			val;
	int			i;

	if (!stack_a || !*stack_a)
		return (-1);
	cur = *stack_a;
	val = cur->value;
	while (cur)
	{
		if (val > cur->value)
			val = cur->value;
		cur = cur->next;
	}
	cur = *stack_a;
	i = 0;
	while (cur)
	{
		if (val == cur->value)
			return (i);
		cur = cur->next;
		i++;
	}
	return (-1);
}

void	push_to_b(t_mylist **a, t_mylist **b)
{
	int	size;
	int	pos;
	int	rotations;

	size = countlist(*a);
	pos = find_smallest(a);
	if (pos <= size / 2)
		while (pos-- > 0)
			rotate(a, "ra");
	else
	{
		rotations = size - pos;
		while (rotations-- > 0)
			reverse_rotate(a, "rra");
	}
	push(a, b, "pb");
}

void	sort_five(t_mylist **stack_a, t_mylist **stack_b)
{	
	push_to_b(stack_a, stack_b);
	push_to_b(stack_a, stack_b);
	if (countlist(*stack_a) == 3)
		sort_three(stack_a);
	else if (countlist(*stack_a) == 2)
		sort_two(stack_a);
	push(stack_b, stack_a, "pa");
	push(stack_b, stack_a, "pa");
}
