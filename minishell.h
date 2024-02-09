/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/09 16:08:30 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	prompt(void);

void	ft_echo(const char *str);
void	ft_cd(const char *path);
char	*ft_pwd(void);

#endif
