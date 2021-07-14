# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 21:41:25 by youncho           #+#    #+#              #
#    Updated: 2021/07/14 16:32:14 by youncho          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philosophers.c \
		actions.c \
		utils.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I.

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	gcc ${CFLAGS} -o ${NAME} ${OBJS} -lpthread

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
