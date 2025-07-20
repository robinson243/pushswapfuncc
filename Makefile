# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romukena <romukena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/12 14:03:53 by romukena          #+#    #+#              #
#    Updated: 2025/07/15 21:13:34 by romukena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = \
    main.c \
    main_algo.c \
    main_algo2.c \
    stack_operations.c \
    stack_operations2.c \
    sort_operations.c \
    list_utils.c \
    memory_utils.c \
    input_validation.c \
    quicksort.c \
    optimized.c

OBJS = $(SRCS:.c=.o)

NAME = push_swap

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

all:	$(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) libft/*.o

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re