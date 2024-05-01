/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:18:24 by xlow              #+#    #+#             */
/*   Updated: 2024/05/01 21:49:55 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exebuns(t_arg *arg, int i, t_list **envll)
{
	char	*cmd;
	char	**args;

	cmd = arg[i].cmd[0];
	args = arg[i].cmd;
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(args);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(args, *envll);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd, "export"))
		ft_export(args, envll);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(args, envll);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(*envll);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(arg, i, envll);
	else
		return (0);
	return (1);
}

static t_arg	heredoc_queue(t_arg args, int *hd_fd)
{
	char	*temp;

	temp = NULL;
	while (1)
	{
		temp = get_next_line(hd_fd[0]);
		if (temp)
		{
			free(temp);
			temp = NULL;
			args.heredoc = 0;
			break ;
		}
	}
	return (args);
}

t_arg	open_heredoc(t_arg args, int i, int *hd_fd)
{
	int	fd[2];

	if (hd_fd && args.heredoc)
		args = heredoc_queue(args, hd_fd);
	if (i == args.in_i - 2)
	{
		pipe(fd);
		dup2(fd[0], args.io[0]);
		ft_heredoc(args.in[i], fd[1]);
		close(fd[1]);
		if (hd_fd)
			write(hd_fd[1], "\n", 1);
	}
	else
		ft_heredoc(args.in[i], -1);
	return (args);
}

void	run_cmds(t_arg *args, t_list **envll)
{
	int		status;
	pid_t	pid;

	args = no_toing(args);
	if (args[0].last)
		run_single(args, envll);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			iterative_piping(args, envll);
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (sig_handler(status))
			get_exit_status(status);
	}
}
