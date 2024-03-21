/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:28 by btan              #+#    #+#             */
/*   Updated: 2024/03/21 17:24:06 by btan             ###   ########.fr       */
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
# include <sys/stat.h>

# define HERE_DOC 578
# define TRUNC 577
# define APPEND 1089

typedef struct s_arg
{
	int		last;
	int		in_i;
	int		out_i;
	int		cmd_i;
	int		heredoc;
	int		io[2];
	char	**in;
	char	**out;
	char	**cmd;
}	t_arg;

// LIBFT
char	**ft_strsplit(char *str, char *token);
char	*ft_strre(char *str, char *find, char *replace);
int		ft_iswhitespace(int c);

// SIGNALS
void	free_strs(char **strs);
void	sigint_parent(int sig);
void	sigint_child(int sig);
void	sighandler_child(void);
void	sighandler_wait(void);
void	sighandler_parent(void);

// PROMPT
char	*init_prompt(t_list *envll);

// ENV
char	**list_to_array(t_list *lst);
int		ft_strslen(char **strs);
char	*expand_env(char *str, t_list *envll);
char 	*expand_all(char *str, t_list *envll);
void	array_to_list(t_list **lst, char **envp);
void	set_shlvl(t_list **envll);

// BUILTINS
void	ft_echo(char **args);
void	ft_cd(char **args, t_list *envll);
char	*ft_pwd(void);
void	ft_env(t_list *envp);
void	ft_export(char *cmd, t_list **envll);
void	ft_unset(char *cmd, t_list **envll);
void	ft_exit(char *str);
void	minibing(void);

// HEREDOC
void	ft_heredoc(char	*eof, int fd);

// HANDLE_ERRORS
int		handle_error(char *vars, char *error);
int		get_exit_status(int status);
int		unshift_exitcode(int status);

// PARSING
void	split_by_space(char *input, char ***split);
void	free_args(t_arg *args);
t_arg	*input_parser(char *input);

// INJECT_SPACE
char	*inject_space(char *input);

// REJOIN_TOKENS
t_arg	*heredoc_order(t_arg *args);
t_arg	*rejoin_tokens(char ***in);

// SPLIT_BY_PIPE
char	***split_by_pipe(char **in);

// SPLIT_BY_SPACE
int		quotes(char c, char *reset);
void	cmd_assign(t_string *cmd, char input);
void	handle_space(t_string *cmd, char ***split, int *cmd_idx, int q);
char	**split_assign(char **split, int *cmd_idx, char *insert);
char	**cleanup_space(t_string *cmd, char ***split, int *cmd_idx);

// RUN_CMD
char	*ft_strsjoin(char **strs);
int		builtin_table(t_arg args, t_list *envll);
void	run_cmds(t_arg *args, t_list *envll);
t_arg	open_heredoc(t_arg args, int i, int *hd_fd);
t_arg	open_files(t_arg args, int *hd_fd);

// FORKS
void	run_single(t_arg *args, t_list *envll);
void	iterative_piping(t_arg *args, t_list *envll);

// DUPS
t_arg	*child_dup(t_arg *args, int *new_fd, int i, int *hd_fd);

#endif
