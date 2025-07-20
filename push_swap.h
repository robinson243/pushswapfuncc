/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:09:54 by romukena          #+#    #+#             */
/*   Updated: 2025/07/20 12:25:06 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

/* Structure de données */
typedef struct s_mylist
{
	int				value;
	int				index;
	int				push_cost;
	bool			above_median;
	bool			cheapest;
	struct s_mylist *target_node;
	struct s_mylist	*next;
	struct s_mylist	*prev;
}						t_mylist;

/*----------------------------------------------------------------------------*/
/*                                input_validation.c                          */
/*----------------------------------------------------------------------------*/
int					is_space(char c);
long				ft_atoi_modif(char *str);
int					check_duplicates(t_mylist *stack);
int					sorted_list(t_mylist *stack);
int					put_in_struct(t_mylist **List, char **av);

/*----------------------------------------------------------------------------*/
/*                                list_utils.c                                */
/*----------------------------------------------------------------------------*/
void				free_list(t_mylist **lst);
t_mylist			*createnode(int value, int index_count);
void				addback(t_mylist **List, int value);
void				add_front(t_mylist **lst, t_mylist *new);
int					countlist(t_mylist *head);
t_mylist	*find_last(t_mylist *stack);

/*----------------------------------------------------------------------------*/
/*                                memory_utils.c                              */
/*----------------------------------------------------------------------------*/
void				free_tableau(char **tab);
int					check_tab(char **tab);
char				**get_args(int ac, char **av);
int					is_valid(int ac, char **av);

/*----------------------------------------------------------------------------*/
/*                                stack_operations.c                          */
/*----------------------------------------------------------------------------*/
void				swap(t_mylist **stack, char *name);
void				push(t_mylist **stack_a, t_mylist **stack_b, char *name);
void				rotate(t_mylist **stack, char *name);
void				reverse_rotate(t_mylist **stack, char *name);

/*----------------------------------------------------------------------------*/
/*                                stack_operations2.c                         */
/*----------------------------------------------------------------------------*/
void				rr(t_mylist **a, t_mylist **b);
void				rrr(t_mylist **a, t_mylist **b);
void				printlist(t_mylist *head);
void				rotate_times(t_mylist **stack, int *cost, char *rot_name,
						char *rev_name);

/*----------------------------------------------------------------------------*/
/*                                sort_operations.c                           */
/*----------------------------------------------------------------------------*/
void				sort_two(t_mylist **stack);
void				sort_three(t_mylist **stack);
void				sort_five(t_mylist **stack_a, t_mylist **stack_b);
int					find_smallest(t_mylist **stack_a);
void				push_to_b(t_mylist **stack_a, t_mylist **stack_b);
void				small_sort(t_mylist **a, t_mylist **b);

/*----------------------------------------------------------------------------*/
/*                                quicksort.c                                 */
/*----------------------------------------------------------------------------*/
void				ft_swap(int *a, int *b);
int					*get_sorted_array(t_mylist *a, int size);
int					partition(int *tab, int deb, int fin);
void				quicksort(int *tab, int deb, int fin);
int					get_position(t_mylist *stack, int index_to_find);

/*----------------------------------------------------------------------------*/
/*                                main_algo.c                                 */
/*----------------------------------------------------------------------------*/
static void	append_node(t_mylist **stack, int n);

/*----------------------------------------------------------------------------*/
/*                                main_algo2.c                                */
/*----------------------------------------------------------------------------*/
int					ft_abs(int n);
t_mylist			*find_cheapest_move(t_mylist *a);
void				execute_move(t_mylist **a, t_mylist **b, t_mylist *move);
void				align_stack_a(t_mylist **a);
void				push_swap(t_mylist **a, t_mylist **b);
void				print_stack(t_mylist *stack);

/*----------------------------------------------------------------------------*/
/*                                optimized.c                                */
/*----------------------------------------------------------------------------*/
static void set_target_a(t_mylist *a, t_mylist *b);
void	sort_stacks(t_mylist **a, t_mylist **b);
void	current_index(t_mylist *stack);
static void move_a_to_b(t_mylist **a, t_mylist **b);
t_mylist	*find_max(t_mylist *stack);
t_mylist	*find_last(t_mylist *stack);
static void cost_analysis_a(t_mylist *a, t_mylist *b);
void	set_cheapest(t_mylist *stack);
void	init_nodes_a(t_mylist *a, t_mylist *b);
void	rotate_both(t_mylist **a, t_mylist **b, t_mylist *cheapest_node);

#endif