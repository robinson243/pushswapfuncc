/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:13:40 by romukena          #+#    #+#             */
/*   Updated: 2025/07/20 12:33:33 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"




static void move_a_to_b(t_mylist **a, t_mylist **b)
{
	t_mylist	*cheapest_node;

	cheapest_node = get_cheapest(*a);
	if (cheapest_node->above_median && cheapest_node->target_node->above_median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median) && !(cheapest_node->target_node->above_median))

	

}

t_mylist	*find_min(t_mylist *stack) //Define a function that searches a stack and returns the node with the smallest number
{
	long			min; //To store the smallest value so far
	t_mylist	*min_node; //To store a pointer that points to the smallest number

	if (!stack)
		return (NULL);
	min = LONG_MAX; //Assign to the smallest value so far, the max long integer
	while (stack) //Loop until the end of the stack is reached
	{
		if (stack->value < min) //Check if the current node value is smaller than the smallest so far
		{
			min = stack->value; //If so, update the smallest number so far
			min_node = stack; //Set the pointer to point to the node with the smallest number so far
		}
		stack = stack->next; //Move to the next node for processing
	}
	return (min_node); 
}

t_mylist	*find_max(t_mylist *stack)
{
	long			max;
	t_mylist	*max_node;

	if (!stack)
		return (NULL);
	max = LONG_MIN;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

t_mylist	*find_last(t_mylist *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

void	current_index(t_mylist *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = countlist(stack) / 2;
	while (stack)
	{
		stack->index = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		++i;
	}
}

static void set_target_a(t_mylist *a, t_mylist *b)
{
	t_mylist	*current_b;
	t_mylist	*target_node;
	long		best_match_index;

	while (a)
	{
		best_match_index = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->value < a->value
				&& current_b->next > best_match_index)
			{
				best_match_index = current_b->value;
				target_node = current_b;
			}
			current_b = current_b->next;
		}
		if (best_match_index == LONG_MIN)
			a->target_node = find_max(b);
		else
			a->target_node = target_node;
		a = a->next;
	}
}

static void cost_analysis_a(t_mylist *a, t_mylist *b)
{
	int	len_a;
	int	len_b;

	len_a = countlist(a);
	len_b = countlist(b);
	while (a)
	{
		a->push_cost = a->index;
		if (!(a->above_median))
			a->push_cost = len_a - (a->index);
		if (a->target_node->above_median)
			a->push_cost += a->target_node->index;
		else
			a->push_cost += len_b - (a->target_node->index);
		a = a->next;
	}
}

void	set_cheapest(t_mylist *stack)
{
	long		cheapest_value;
	t_mylist	*cheapest_node;

	if (!stack)
		return ;
	cheapest_value = LONG_MAX;
	while (stack)
	{
		if (stack->push_cost < cheapest_value)
		{
			cheapest_value = stack->push_cost;
			cheapest_node = stack;
		}
		stack = stack->next;
	}
}

void	init_nodes_a(t_mylist *a, t_mylist *b)
{
	current_index(a);
	current_index(b);
	set_target_a(a, b);
	cost_analysis_a(a, b);
	set_cheapest(a);
}

void	sort_stacks(t_mylist **a, t_mylist **b)
{
	int	len_a;

	len_a = countlist(*a);
	if (len_a-- > 3 && !sorted_list(*a))
		push(a, b, "pa");
	if (len_a-- > 3 && !sorted_list(*a))
		push(a, b, "pa");
	while (len_a-- > 3 && !sorted_list(*a))
	{
		init_nodes_a(*a,*b);
		move_a_to_b(a, b);
	}
	sort_three(a);
	while (*b)
	{
		init_nodes_a(*a,*b);
		move_b_to_a(a, b);
	}
	current_index(*a);
	min_on_top(a);
}
