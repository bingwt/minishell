#ifndef MSPIPING_H
# define MSPIPING_H

# include "../minishell.h"

// RUN_CMD
int		builtin_table(t_arg args, t_list *envll);
void	run_cmds(t_arg *args, char **envp, t_list *envll);
void	dup_pipes(t_arg args, int *pipe);
void	open_heredoc(char *eof, int last, int *io);
t_arg	open_files(t_arg args);

// FORKS
void	run_single(t_arg *args, char **envp, t_list *envll);
void	minishell_piping(t_arg *args, char **envp, t_list *envll);

#endif
