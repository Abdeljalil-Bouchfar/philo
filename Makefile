# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdeljalilbouchfar <abdeljalilbouchfar@    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 15:48:07 by abouchfa          #+#    #+#              #
#    Updated: 2022/09/08 21:56:17 by abdeljalilb      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = gcc -Wall -Wextra -Werror -pthread #-fsanitize=thread -g

CFILES = philo.c \
		time.c \
		routine.c \
		Utils/ft_atoi.c \
		Utils/ft_putstr_fd.c \
		Utils/print_error.c \
		Utils/alloc.c \
		Utils/fork_lst_utils.c \

CBONUS_FILES = bonus.c

all: $(NAME)

$(NAME): $(CFILES)
	$(CFLAGS) $(CFILES) -o $(NAME)

bonus: all

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
.PHONY: all clean fclean re