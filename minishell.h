/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/26 23:44:20 by btan             ###   ########.fr       */
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

void	free_strs(char **strs);

void	handle_signal(int sig);

char	*init_prompt(void);
char	**init_envp(void);
void	init_envll(t_list **envp);
char	**list_to_array(t_list *lst);

void	ft_echo(const char *str);
void	ft_cd(const char *path);
char	*ft_pwd(void);
void	ft_env(char **envp);
void	ft_export(char **envp);

void	run_cmd(char *cmd, char ***envp);

#endif
