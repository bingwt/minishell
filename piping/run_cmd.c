/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:18:24 by xlow              #+#    #+#             */
/*   Updated: 2024/03/18 19:29:36 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_table(t_arg args, t_list *envll)
{
	char	*cmd;

	cmd = ft_strsjoin(args.cmd);
	if (!ft_strcmp(args.cmd[0], "echo"))
		ft_echo(cmd + 4);
	else if (!ft_strcmp(args.cmd[0], "cd"))
		ft_cd(cmd + 2, envll);
	else if (!ft_strcmp(args.cmd[0], "pwd"))
		printf("%s\n", ft_pwd());
	else if (!ft_strcmp(args.cmd[0], "export"))
		ft_export(cmd, &envll);
	else if (!ft_strcmp(args.cmd[0], "unset"))
		ft_unset(cmd, &envll);
	else if (!ft_strcmp(args.cmd[0], "env"))
		ft_env(envll);
	else if (!ft_strcmp("exit", args.cmd[0]))
		exit(0);
	else
	{
		free(cmd);
		return (0);
	}
	free(cmd);
	return (1);
}

static void	heredoc_queue(int *hd_fd)
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
			break ;
		}
	}
}

t_arg	open_heredoc(t_arg args, int i, int *hd_fd)
{
	int		fd[2];
	char	*temp;

	temp = NULL;
	if (hd_fd && args.heredoc)
		heredoc_queue(hd_fd);
	if (i == args.in_i - 2)
	{
		pipe(fd);
		dup2(fd[0], args.io[0]);
		ft_heredoc(args.in[i], fd[1]);
		close(fd[1]);
		if (hd_fd)
			while (--i != -2)
				write(hd_fd[1], "\n", 1);
	}
	else
		ft_heredoc(args.in[i], -1);
	return (args);
}

t_arg	open_files(t_arg args, int *hd_fd)
{
	int	i;

	i = 0;
	while (i < args.in_i - 1)
	{
		if (!ft_strcmp(args.in[i++], "<"))
			dup2(open(args.in[i], O_RDONLY), args.io[0]);
		else
			args = open_heredoc(args, i, hd_fd);
		if (args.io[0] == -1)
			perror("open");
		i++;
	}
	i = 0;
	while (i < args.out_i - 1)
	{
		if (!ft_strcmp(args.out[i++], ">>"))
			dup2(open(args.out[i++], APPEND, 0644), args.io[1]);
		else
			dup2(open(args.out[i++], TRUNC, 0644), args.io[1]);
		if (args.io[1] == -1)
			perror("open");
	}
	return (args);
}

void	run_cmds(t_arg *args, t_list *envll)
{
	int		exit_status;
	pid_t	pid;

	if (args[0].last)
		run_single(args, list_to_array(envll), envll);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			signal(SIGINT, sigint_child);
			signal(SIGQUIT, SIG_DFL);
			iterative_piping(args, envll);
		}
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &exit_status, 0);
		signal(SIGINT, sigint_parent);
		signal(SIGQUIT, SIG_DFL);
	}
}
/*
int	main(int argc, char **argv, char **envp)
{
	(void)	argc;
	char	*str;
	t_list	*envll;
	t_arg	*args;
	str = malloc(ft_strlen(argv[1]) + 1);
	str = strcpy(str, argv[1]);
	args = input_parser(str);
	envll = NULL;
	array_to_list(&envll, envp);
	run_cmds(args, envll);
	return (0);
}
*/
/*
#include "minishell.h"

int	wait_cids(t_arg *args, pid_t *cids)
{
	int	i;
	int	j;
	int	exit_status;

	i = 0;
	j = 0;
	while (!args[i].last)
		i++;
	while (j <= i)
	{
		waitpid(cids[j], &exit_status, 0);
		j++;
	}
	return (exit_status);
}

pid_t	*read_cids(t_arg *args, int *pipe)
{
	int		i;
	int		j;
	pid_t	*cid;
	char	*temp;

	close(pipe[1]);
	i = 0;
//	while (i < 100000)
//		i++;
//	i = 0;
	while (!args[i].last)
		i++;
	temp = NULL;
	cid = ft_calloc(i + 1, sizeof(pid_t));
	j = 0;
	while (j <= i)
	{
		temp = get_next_line(pipe[0]);
		cid[j] = ft_atoi(temp);
		free(temp);
		j++;
	}
	close(pipe[0]);
	return (cid);
}

void	write_cid(pid_t pid, int pipe)
{
	char	*res;

	res = ft_itoa(pid);
	write(pipe, res, ft_strlen(res));
	write(pipe, "\n", 1);
	close(pipe);
	free(res);
}
*/
/*
void	execute(t_arg *args, char **envp, t_list *envll, int i)
{
	char	*path;

	args[i] = open_files(args[i]);
//	dup_fds(args, i);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	close(args[i].io[0]), close(args[i].io[1]);
	if (builtin_table(args[i], envll))
		exit(0);
	if (!access(args[i].cmd[0], X_OK))
		execve(args[i].cmd[0], args[i].cmd, envp);
	path = get_path(args[i].cmd[0], envll);
	if (!path)
	{
		handle_error(args[i].cmd[0], "CMD_NOT_FOUND");
		exit(127);
	}
	execve(path, args[i].cmd, envp);
	perror("execve"), free_args(args), exit(1);
}
*/
/*
void	close_pipes(t_arg *args)
{
	int	i;

	i = 0;
	while (!args[i].last)
	{
		close(args[i].fd[0]);
		close(args[i].fd[1]);
		close(args[i].io[0]);
		close(args[i].io[1]);
		i++;
	}
	close(args[i].fd[0]);
	close(args[i].fd[1]);
	close(args[i].io[0]);
	close(args[i].io[1]);
}

void	run_first(t_arg *args, char **envp, t_list *envll, int i)
{
	char	*path;

	dup2(args[i + 1].fd[1], args[i].io[1]);
	args[i] = open_files(args[i]);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	close_pipes(args);
	if (builtin_table(args[i], envll))
		exit(0);
	if (!access(args[i].cmd[0], X_OK))
		execve(args[i].cmd[0], args[i].cmd, envp);
	else
	{
		path = get_path(args[i].cmd[0], envll);
		if (!path)
		{
			handle_error(args[i].cmd[0], "CMD_NOT_FOUND");
			exit(127);
		}
		execve(path, args[i].cmd, envp);
	}
	perror("execve"), free_args(args), exit(1);
}

void	run_middle(t_arg *args, char **envp, t_list *envll, int i)
{
	char	*path;

	dup2(args[i].fd[0], args[i].io[0]);
	dup2(args[i + 1].fd[1], args[i].io[1]);
	args[i] = open_files(args[i]);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	close_pipes(args);
	if (builtin_table(args[i], envll))
		exit(0);
	if (!access(args[i].cmd[0], X_OK))
		execve(args[i].cmd[0], args[i].cmd, envp);
	else
	{
		path = get_path(args[i].cmd[0], envll);
		if (!path)
		{
			handle_error(args[i].cmd[0], "CMD_NOT_FOUND");
			exit(127);
		}
		execve(path, args[i].cmd, envp);
	}
	perror("execve"), free_args(args), exit(1);
}

void	run_last(t_arg *args, char **envp, t_list *envll, int i)
{
	char	*path;

	dup2(args[i].fd[0], args[i].io[0]);
	args[i] = open_files(args[i]);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	close_pipes(args);
	if (builtin_table(args[i], envll))
		exit(0);
	if (!access(args[i].cmd[0], X_OK))
		execve(args[i].cmd[0], args[i].cmd, envp);
	else
	{
		path = get_path(args[i].cmd[0], envll);
		if (!path)
		{
			handle_error(args[i].cmd[0], "CMD_NOT_FOUND");
			exit(127);
		}
		execve(path, args[i].cmd, envp);
	}
	perror("execve"), free_args(args), exit(1);
}

void	runs(t_arg *args, char **envp, t_list *envll, int i)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (!i)
			run_first(args, envp, envll, i);
		else if (args[i].last)
			run_last(args, envp, envll, i);
		else
			run_middle(args, envp, envll, i);
	}
	close_pipes(args);
	exit(0);
}

void	loop(t_arg *args, char **envp, t_list *envll, int i)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		runs(args, envp, envll, i);
	else if (!args[i].last)
		loop(args, envp, envll, i + 1);
	if (args[i].last)
	{
		close_pipes(args);
		exit(0);
	}
	while(wait(0))
		;
	close_pipes(args);
	exit(0);
}

void	forks(t_arg *args, char **envp, t_list *envll, int i)
{
	int		exit_status;
	pid_t	pid;

	if (args[0].last)
		run_single(args, envp, envll);
	else
	{
		pid = fork();
		if (!pid)
			loop(args, envp, envll, i);
		close_pipes(args);
		waitpid(pid, &exit_status, 0);
	}
}
*/
/*
void	dup_fds(t_arg *args, int i)
{
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	if (args[i].io[0] != 0)
		close(args[i].io[0]);
	if (args[i].io[1] != 1)
		close(args[i].io[1]);
}
*/
/*
void	run_cmds(t_arg *args, t_list *envll, char **envp, int i)
{
	int		exit_status;
	pid_t	pid;

	if (args[0].last)
		run_single(args, envp, envll);
	else
	{
		if (pipe(args[i].new_pipe) < 0)
			perror("pipe");
		pid = fork();
		if (pid < 0)
			perror("minibing");
		if (!pid)
		{
			if (!args[i].last)
				args[i].io[1] = args[i].new_pipe[1];
			else
				args[i].io[0] = args[i].old_pipe[0];
			if (i != 0 && !args[i].last)
				args[i].io[0] = args[i].old_pipe[0];
			execute(args, envp, envll, i);
		}
		if (!args[i].last)
		{
			args[i + 1].old_pipe[0] = args[i].new_pipe[0];
			args[i + 1].old_pipe[1] = args[i].new_pipe[1];
			run_cmds(args, envll, envp, i + 1);
		}
		while (waitpid(-1, &exit_status, WNOHANG))
				;
	}
}
*/
/*
void	run_cmds(t_arg *args, t_list *envll, char **envp, int i)
{
	int		exit_status;
	pid_t	pid;

	if (args[0].last)
		run_single(args, envp, envll);
	else
	{
		pipe(args[i].new_pipe);
		pid = fork();
		if (!pid)
		{
			if (!i)
			{
				dup2(args[i].new_pipe[1], args[i].io[1]);
				close(args[i].new_pipe[0]);
				close(args[i].new_pipe[1]);
				execute(args, envp, envll, i);
			}
			else if (args[i].last)
			{
				dup2(args[i].old_pipe[0], args[i].io[0]);
				close(args[i].old_pipe[0]);
				close(args[i].old_pipe[1]);
				close(args[i].new_pipe[0]);
				close(args[i].new_pipe[1]);
				execute(args, envp, envll, i);
			}
			else
			{
				dup2(args[i].old_pipe[0], args[i].io[0]);
				dup2(args[i].new_pipe[1], args[i].io[1]);
				close(args[i].old_pipe[0]);
				close(args[i].old_pipe[1]);
				close(args[i].new_pipe[0]);
				close(args[i].new_pipe[1]);
				execute(args, envp, envll, i);
			}
		}
		else if (!args[i].last)
		{
			args[i + 1].old_pipe[0] = dup(args[i].new_pipe[0]);
			args[i + 1].old_pipe[1] = dup(args[i].new_pipe[1]);
			run_cmds(args, envll, envp, i + 1);
		}
		if (!i)
				while(waitpid(-1, &exit_status, 0))
					;
	}
}*/
/*
void	dup_fds(t_arg *args, int *n, int i)
{
	dup2(n[0], args[i].io[0]);
	dup2(args[0].fd[1], args[i].io[1]);
	close(args[0].fd[0]);
	close(args[0].fd[1]);
	close(n[0]);
	close(n[1]);
}

void	run_cmds(t_arg *args, t_list *envll, char **envp, int i)
{
	int		new[2];
	int		exit_status;
	pid_t	pid;

	if (args[0].last)
		run_single(args, envp, envll);
	pipe(new);
	pid = fork();
	if (!pid)
	{
		if (!i)
		{
			dup2(new[1], args[i].io[1]);
			close(new[0]);
			close(new[1]);
		}
		else if (args[i].last)
		{
			dup2(args[0].fd[0], args[i].io[0]);
			close(new[0]);
			close(new[1]);
			close(args[0].fd[0]);
			close(args[0].fd[1]);
		}
		else
			dup_fds(args, new, i);
		execute(args, envp, envll, i);
	}
	else if (!args[i].last)
	{
		dup2(new[0], args[0].fd[0]);
		dup2(new[1], args[0].fd[1]);
		run_cmds(args, envll, envp, i + 1);
	}
	while (waitpid(pid, &exit_status, 0))
		;
}
*/
//
//int	main(int argc, char **argv, char **envp)
//{
//	(void)	argc;
//	char	*str;
//	t_list	*envll;
//	t_arg	*args;
//	str = malloc(ft_strlen(argv[1]) + 1);
//	str = strcpy(str, argv[1]);
//	args = input_parser(str);
//	envll = NULL;
//	array_to_list(&envll, envp);
//	run_cmds(args, envp, envll);
//	return (0);
//}
