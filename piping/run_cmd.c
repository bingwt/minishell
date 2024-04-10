/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:18:24 by xlow              #+#    #+#             */
/*   Updated: 2024/04/11 02:01:13 by btan             ###   ########.fr       */
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
	if (!strcmp(cmd, "echo"))
		ft_echo(args);
	else if (!strcmp(cmd, "cd"))
		ft_cd(args, *envll);
	else if (!strcmp(cmd, "pwd"))
		ft_pwd();
	else if (!strcmp(cmd, "export"))
		ft_export(args, envll);
	else if (!strcmp(cmd, "unset"))
		ft_unset(args, envll);
	else if (!strcmp(cmd, "env"))
		ft_env(*envll);
	else if (!strcmp(cmd, "exit"))
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

t_arg open_files(t_arg args, int *hd_fd)
{
	int cock;
	int i;

	i = 0;
	while (i < args.out_i - 1)
	{
		if (!ft_strcmp(args.out[i++], ">>"))
		{
			cock = open(args.out[i++], APPEND, 0644);
			if (cock == -1)
			{
				handle_error(args.out[i - 1], NO_PERMS_OPEN);
				args.io[0] = -1;
				break;
			}
			else
				dup2(cock, args.io[1]);
		}
		else
		{
			cock = open(args.out[i++], TRUNC, 0644);
			if (cock == -1)
			{
				if (!access(args.in[i - 1], F_OK))
					handle_error(args.out[i - 1], NO_PERMS_OPEN);
				else
					handle_error(args.out[i - 1], NO_FILE);
				args.io[1] = -1;
				break;
			}
			else
				dup2(cock, args.io[1]);
		}
	}
	i = 0;
	while (i < args.in_i - 1)
	{
		if (!ft_strcmp(args.in[i++], "<"))
		{
			cock = open(args.in[i++], O_RDONLY);
			if (cock == -1)
			{
				// if (!access(args.in[i - 1], F_OK))
				if (is_dir(args.in[i - 1]))
					handle_error(args.in[i - 1], NO_PERMS_OPEN);
				else
					handle_error(args.in[i - 1], NO_FILE);
				args.io[1] = -1;
				break;
			}
			else
				dup2(cock, args.io[0]);
		}
		else
			args = open_heredoc(args, i++, hd_fd);
	}
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
		signal(SIGINT, sig_wait);
		waitpid(pid, &status, 0);
		if (sig_handler(status))
			get_exit_status(status);
	}
}
