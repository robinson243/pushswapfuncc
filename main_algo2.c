/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_algo2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 01:09:22 by romukena          #+#    #+#             */
/*   Updated: 2025/07/20 01:55:57 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Le vrai */
void	push_swap(t_mylist **a, t_mylist **b)
{
	int			size;
	int			*sorted;
	t_mylist	*move;

	if (!a || !*a || countlist(*a) <= 1 || sorted_list(*a))
		return ;
	size = countlist(*a);
	sorted = get_sorted_array(*a, size);
	if (!sorted)
		return ;
	get_index_for_list(sorted, *a, size);
	free(sorted);
	if (size <= 5)
		return (small_sort(a, b));
	while (countlist(*a) > 3)
		push_to_b(a, b);
	sort_three(a);
	while (*b)
	{
		calculate_move_cost(*a, *b);
		move = find_cheapest_move(*b);
		execute_move(a, b, move);
	}
	align_stack_a(a);
}
 
/* Le faux */
/* void push_swap(t_mylist **a, t_mylist **b)
{
    int size = countlist(*a);
    int *sorted;
    // t_mylist *move;

    if (size <= 1 || sorted_list(*a))
        return;
    sorted = get_sorted_array(*a, size);
    if (!sorted)
        return;
    get_index_for_list(sorted, *a, size);
    free(sorted);
    if (size <= 5)
        return small_sort(a, b);
    radix_sort(a, b);
	// align_stack_a(a);
} */
