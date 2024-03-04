# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 19:26:56 by btan              #+#    #+#              #
#    Updated: 2024/03/04 16:09:49 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES = .

SRCS = env.c \
	   signals.c \
	   prompt.c \
	   handle_errors.c \
	   builtins/ft_echo.c \
	   builtins/ft_cd.c \
	   builtins/ft_pwd.c \
	   builtins/ft_env.c \
	   builtins/ft_export.c \
	   builtins/ft_unset.c \
	   builtins/minibing.c \
	   execute.c \
	   main.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES)

CLIBS = -lreadline

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) libft/libft.a $(CLIBS)

libft/libft.a:
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJECTS) $(NAME).a

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
