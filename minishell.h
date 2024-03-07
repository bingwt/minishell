/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:28 by btan              #+#    #+#             */
/*   Updated: 2024/03/07 16:21:22 by xlow             ###   ########.fr       */
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

# define HERE_DOC 578
# define TRUNC 577
# define APPEND 1089

typedef struct s_arg
{
	int		last;
	int		in_i;
	int		out_i;
	int		cmd_i;
	int		io[2];
	char	**in;
	char	**out;
	char	**cmd;
}	t_arg;

#include "parsing/msparsing.h"
#include "piping/mspiping.h"

// SIGNALS
void	free_strs(char **strs);
void	handle_signal(int sig);

// PROMPT
char	*init_prompt(t_list *envll);

// ENV
char	**list_to_array(t_list *lst);
char	*expand_env(char *str, t_list *envll);
void	array_to_list(t_list **lst, char **envp);

// BUILTINS
void	ft_echo(const char *str);
void	ft_cd(const char *path, t_list *envll);
char	*ft_pwd(void);
void	ft_env(t_list *envp);
void	ft_export(char *cmd, t_list **envll);
void	ft_unset(char *cmd, t_list **envll);
void	minibing(void);

// EXECUTE
char	*get_path(char *cmd, t_list *envll);
int		handle_error(char *vars, char *error);
void	run_cmd(char *cmd, t_list *envll);

// HEREDOC
void	ft_heredoc(char	*eof, int fd);

#endif
