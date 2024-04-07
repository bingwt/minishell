# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 19:26:56 by btan              #+#    #+#              #
#    Updated: 2024/04/05 23:16:40 by xlow             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES = .

SRCS = signals.c \
	   prompt.c \
	   handle_errors.c \
	   ft_iswhitespace.c \
	   minishell_utils.c \
	   builtins/ft_echo.c \
	   builtins/ft_cd.c \
	   builtins/ft_pwd.c \
	   builtins/ft_env.c \
	   builtins/ft_export.c \
	   builtins/ft_unset.c \
	   builtins/ft_exit.c \
	   builtins/ft_heredoc.c \
	   builtins/minibing.c \
	   parsing/inject_space.c \
	   parsing/rejoin_tokens.c \
	   parsing/split_by_pipe.c \
	   parsing/split_by_space.c \
	   parsing/parsing.c \
	   parsing/expand_env.c \
	   piping/forks.c \
	   piping/ft_strsjoin.c \
	   piping/run_cmd.c \
	   piping/dups.c \
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

run: all
	clear
	./minishell

.PHONY: all clean fclean re debug
