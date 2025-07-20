/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:48:43 by romukena          #+#    #+#             */
/*   Updated: 2025/07/20 00:56:13 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

int	is_space(char c)
{
	if (c == 32 || c == '\f' || c == '\n' || c == '\r')
		return (1);
	else if (c == '\t' || c == '\v')
		return (1);
	return (0);
}

long	ft_atoi_modif(char *str)
{
	long int	res;
	int			minus;

	res = 0;
	minus = 1;
	if (!str || *str == '\0')
		return (99999999999999);
	while (is_space(*str))
		str++;
	if (*str == '\0')
		return (99999999999999);
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			minus *= -1;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
		if ((minus == -1 && res > -(long)INT_MIN)
			|| (minus == 1 && res > INT_MAX))
			return (99999999999999);
	}
	if (*str != '\0')
		return (99999999999999);
	return ((res * minus));
}

int	check_duplicates(t_mylist *stack)
{
	t_mylist	*cur;
	t_mylist	*nextone;

	cur = stack;
	nextone = stack;
	if (!stack)
		return (0);
	while (cur)
	{
		nextone = cur->next;
		while (nextone)
		{
			if (cur->value == nextone->value)
				return (1);
			nextone = nextone->next;
		}
		cur = cur->next;
	}
	return (0);
}

int	sorted_list(t_mylist *stack)
{
	t_mylist	*current;
	t_mylist	*nextone;

	current = stack;
	nextone = stack;
	if (!stack)
		return (1);
	if (!stack->next)
		return (1);
	while (current)
	{
		nextone = current->next;
		if (nextone && current->value > nextone->value)
			return (0);
		current = current->next;
	}
	return (1);
}

int	put_in_struct(t_mylist **List, char **av)
{
	int		i;
	long	num;

	i = 0;
	if (!av || !av[0])
		return (1);
	while (av[i])
	{
		num = ft_atoi_modif(av[i]);
		if (num == 99999999999999 || num > INT_MAX || num < INT_MIN)
			return (1);
		append_node(List, num);
		i++;
	}
	return (0);
}
