# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 19:26:56 by btan              #+#    #+#              #
#    Updated: 2024/02/08 19:59:42 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES = .

SRCS = utils.c \
	   builtins.c \
	   main.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

CLIBS = -lreadline

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -I$(INCLUDES) $(CLIBS)

clean:
	rm -rf $(OBJECTS) $(NAME).a

fclean: clean
	rm -rf $(NAME)


re: fclean all

debug: CFLAGS += -g -fsanitize=thread
debug: re

.PHONY: all clean fclean re debug
