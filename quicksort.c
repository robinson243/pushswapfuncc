/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 01:10:50 by romukena          #+#    #+#             */
/*   Updated: 2025/07/15 15:35:30 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	partition(int *tab, int deb, int fin)
{
	int	pivot;
	int	i;
	int	j;

	pivot = tab[fin];
	i = deb;
	j = deb;
	while (j < fin)
	{
		if (tab[j] < pivot)
		{
			ft_swap(&tab[i], &tab[j]);
			i++;
		}
		j++;
	}
	ft_swap(&tab[i], &tab[fin]);
	return (i);
}

void	quicksort(int *tab, int deb, int fin)
{
	int	p;

	if (deb < fin)
	{
		p = partition(tab, deb, fin);
		quicksort(tab, deb, p - 1);
		quicksort(tab, p + 1, fin);
	}
}

int	*get_sorted_array(t_mylist *a, int size)
{
	int	*tab;
	int	i;

	if (!a || size <= 0)
		return (NULL);
	tab = malloc(sizeof(int) * size);
	if (!tab)
		return (NULL);
	i = 0;
	while (a)
	{
		tab[i] = a->value;
		a = a->next;
		i++;
	}
	quicksort(tab, 0, size - 1);
	return (tab);
}

int	get_position(t_mylist *stack, int index_to_find)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index_to_find)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}
