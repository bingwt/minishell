# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 19:26:56 by btan              #+#    #+#              #
#    Updated: 2024/02/18 21:09:25 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES = .

SRCS = signals.c \
	   prompt.c \
	   builtins.c \
	   execute.c \
	   main.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

CLIBS = -lreadline

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a
	$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME) -I$(INCLUDES) $(CLIBS)

libft/libft.a:
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJECTS) $(NAME).a

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -g -fsanitize=thread
debug: re

.PHONY: all clean fclean re debug
