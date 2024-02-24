/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 08:21:32 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CYELLOW "\001\e[0;31m\002"
# define RESET   "\001\e[0m\002"

# include "libft/libft.h"
# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termios.h>

// SIGNALS
void	handle_signal(int sig);

// PROMPT
char	*get_hostname(void);
char	*get_user(void);
char	*init_prompt(void);

// ENV
char	**init_env(void);

// BUILTINS
void	ft_echo(const char *str);
void	ft_cd(const char *path);
char	*ft_pwd(void);

// EXECUTE
char	*get_path(char *cmd);
int		handle_error(char *vars, char *error);
int		builtin_table(char *cmd);
void	run_cmd(char *cmd);

// SPLIT_BY_SPACE
int		quotes(char c, char *reset);
void	cmd_assign(t_string *cmd, char input);
char	**split_assign(char **split, int *cmd_idx, char *insert);
void	handle_space(t_string *cmd, char ***split, int *cmd_idx, int q);
char	**cleanup_space(t_string *cmd, char ***split, int *cmd_idx);

// PARSING
void	split_by_space(char *input, char ***split);
char	**input_parser(char *input);
#endif
