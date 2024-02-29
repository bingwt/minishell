/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/29 16:12:46 by btan             ###   ########.fr       */
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

typedef struct s_arg
{
	int		last;
	int		in_i;
	int		out_i;
	int		cmd_i;
	char	**in;
	char	**out;
	char	**cmd;
}	t_arg;

// SIGNALS
void	free_strs(char **strs);
void	handle_signal(int sig);

// PROMPT
char	*get_hostname(void);
char	*get_user(void);
char	*init_prompt(void);

// ENV
char	**list_to_array(t_list *lst);
char	*expand_env(char *str, t_list *envll);
void	array_to_list(t_list **lst, char **envp);

// BUILTINS
void	ft_echo(const char *str);
void	ft_cd(const char *path);
char	*ft_pwd(void);
void	ft_env(t_list *envp);
void	ft_export(char *cmd, t_list **envll);
void	ft_unset(char *cmd, t_list **envll);
void	minibing(void);

// EXECUTE
char	*get_path(char *cmd);
int		handle_error(char *vars, char *error);
void	run_cmd(char *cmd, t_list *envll);

// SPLIT_BY_SPACE
int		quotes(char c, char *reset);
void	cmd_assign(t_string *cmd, char input);
char	**split_assign(char **split, int *cmd_idx, char *insert);
void	handle_space(t_string *cmd, char ***split, int *cmd_idx, int q);
char	**cleanup_space(t_string *cmd, char ***split, int *cmd_idx);

// PARSING
void	split_by_space(char *input, char ***split);
t_arg	*input_parser(char *input);

// INJECT_SPACE
char	*inject_space(char *input);

// SPLIT_BY_PIPE
char	***split_by_pipe(char **in);

// REJOIN_TOKENS
t_arg	*rejoin_tokens(char ***in);

#endif
