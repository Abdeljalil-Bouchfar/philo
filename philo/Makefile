# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 15:48:07 by abouchfa          #+#    #+#              #
#    Updated: 2022/09/13 23:23:49 by abouchfa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = gcc -Wall -Wextra -Werror -fsanitize=thread

CFILES = philo.c \
		time.c \
		routine.c \
		Utils/validate_input.c \
		Utils/ft_atoi.c \
		Utils/ft_strcmp.c \
		Utils/ft_putstr_fd.c \

all: $(NAME)

$(NAME): $(CFILES)
	$(CFLAGS) $(CFILES) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
.PHONY: all clean fclean re