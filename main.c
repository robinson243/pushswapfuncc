/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:32:18 by romukena          #+#    #+#             */
/*   Updated: 2025/07/19 22:13:39 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_sort(t_mylist **a, t_mylist **b)
{
	int	size;

	size = countlist(*a);
	if (size == 2)
		sort_two(a);
	else if (size == 3)
		sort_three(a);
	else if (size <= 5)
		sort_five(a, b);
}

void	print_stack(t_mylist *stack)
{
	while (stack)
	{
		printf("%d ", stack->value);
		stack = stack->next;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_mylist	*stack_a;
	t_mylist	*stack_b;
	char		**args;

	stack_a = NULL;
	stack_b = NULL;
	args = get_args(ac, av);
	if (ac < 2 || !args || put_in_struct(&stack_a, args) != 0)
	{
		write(2, "Error\n", 6);
		free_tableau(args);
		return (1);
	}
	free_tableau(args);
	if (check_duplicates(stack_a))
	{
		write(2, "Error\n", 6);
		free_list(&stack_a);
		return (1);
	}
	push_swap(&stack_a, &stack_b);
	free_list(&stack_a);
	free_list(&stack_b);
	return (0);
}

