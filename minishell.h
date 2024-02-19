/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/19 20:50:44 by xlow             ###   ########.fr       */
/*   Updated: 2024/02/18 21:08:33 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

void	handle_signal(int sig);

char	*init_prompt(void);

void	ft_echo(const char *str);
void	ft_cd(const char *path);
char	*ft_pwd(void);

int		builtin_table(char *cmd);
void	run_cmd(char *cmd);

#endif
