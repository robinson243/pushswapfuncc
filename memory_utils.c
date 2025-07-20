/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:49:31 by romukena          #+#    #+#             */
/*   Updated: 2025/07/15 15:25:18 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	free_tableau(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

/* int	free_node(t_mylist *node)
{
	free(node);
	return (0);
} */

int	check_tab(char **tab)
{
	int		i;
	long	val;

	i = 0;
	while (tab[i])
	{
		val = ft_atoi_modif(tab[i]);
		if (val == 99999999999999 || val > INT_MAX || val < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

char	**get_args(int ac, char **av)
{
	int		i;
	char	**args;

	i = 0;
	if (ac <= 1)
		return (NULL);
	if (ac == 2)
		return (ft_split(av[1], ' '));
	else
	{
		args = malloc(sizeof(char *) * (ac));
		if (!args)
			return (NULL);
		while (i < (ac - 1))
		{
			args[i] = ft_strdup(av[i + 1]);
			if (!args[i])
				return (free_tableau(args), NULL);
			i++;
		}
		args[i] = NULL;
	}
	return (args);
}

int	is_valid(int ac, char **av)
{
	char		**tab;
	t_mylist	*head;

	head = NULL;
	tab = get_args(ac, av);
	if (!tab)
		return (0);
	if (check_tab(tab))
		return (free_tableau(tab), 0);
	if (put_in_struct(&head, tab))
	{
		free_tableau(tab);
		free_list(&head);
		return (0);
	}
	if (check_duplicates(head))
	{
		free_tableau(tab);
		free_list(&head);
		return (0);
	}
	free_list(&head);
	free_tableau(tab);
	return (1);
}
