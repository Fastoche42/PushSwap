# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 15:47:43 by fl-hote           #+#    #+#              #
#    Updated: 2022/09/25 20:12:31 by fl-hote          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= push_swap.c push_swap_utils.c push_swap_common.c \
				push_swap_parse.c push_swap_stack.c push_swap_phase2.c \
				ft_split.c
SRCS_B		= checker.c push_swap_common.c push_swap_parse.c ft_split.c \
				push_swap_stack.c get_next_line.c get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)

NAME		= push_swap
CHCKR		= checker

#GNL			= get_next_line/

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -I. #-g -fsanitize=address
#LDFLAGS 	= -L$(GNL) -lgnl

all: $(NAME)

%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus: $(OBJS_B)
#		make -C $(GNL)
#		$(CC) $(CFLAGS) -I$(GNL) -o $(CHCKR) $(LDFLAGS) $(OBJS_B)
		$(CC) $(CFLAGS) -o $(CHCKR) $(OBJS_B)

#$(GNL)/libgnl.a:
#		make -C $(GNL)

clean:
		rm -f $(OBJS)

cleanb:
		rm -f $(OBJS_B)

fclean: clean
		rm -f $(NAME)

fcleanb: cleanb
		rm -f $(CHCKR)

re: fclean all

rebonus: fcleanb bonus

.PHONY: all bonus clean fclean re rebonus
