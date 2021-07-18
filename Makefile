# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 21:41:25 by youncho           #+#    #+#              #
#    Updated: 2021/07/18 21:46:39 by youncho          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./philo/philo
NAME_BONUS = ./philo_bonus/philo_bonus

SRCS =	./philo/philosophers.c \
		./philo/actions.c \
		./philo/utils.c

SRCS_BONUS =	./philo_bonus/philosophers_bonus.c \
				./philo_bonus/actions_bonus.c \
				./philo_bonus/utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

GCC_FLAG = -Wall -Werror -Wextra -pthread
CC = gcc $(GCC_FLAG)

all: $(NAME) $(NAME_BONUS)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o ${NAME} ${OBJS} -I./includes

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) -o ${NAME_BONUS} ${OBJS_BONUS} -I./includes

bonus: $(NAME_BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
