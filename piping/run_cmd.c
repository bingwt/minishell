/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:18:24 by xlow              #+#    #+#             */
/*   Updated: 2024/03/11 14:51:21 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_table(t_arg args, t_list *envll)
{
	char	*cmd;

	cmd = ft_strsjoin(args.cmd);
	//cmd = ft_strjoin_strs(args.cmd);
	//printf("%s\n", cmd);
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
	else if (!ft_strcmp(args.cmd[0], "minibing"))
		minibing();
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

void	open_heredoc(char *eof, int last, int *io)
{
	int	fd[2];

	if (last)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		*io = fd[0];
		ft_heredoc(eof, fd[1]);
	}
	else
		ft_heredoc(eof, -1);
}

t_arg	open_files(t_arg args)
{
	int	i;

	i = 0;
	while (i < args.in_i - 1)
	{
		if (!ft_strcmp(args.in[i++], "<"))
			args.io[0] = open(args.in[i], O_RDONLY);
		else
			open_heredoc(args.in[i], args.last, &args.io[0]);
		if (args.io[0] == -1)
			perror("open");
		i++;
	}
	i = 0;
	while (i < args.out_i - 1)
	{
		if (!ft_strcmp(args.out[i++], ">>"))
			args.io[1] = open(args.out[i++], APPEND, 0644);
		else
			args.io[1] = open(args.out[i++], TRUNC, 0644);
		if (args.io[1] == -1)
			perror("open");
	}
	return (args);
}

void	dup_pipes(t_arg args, int *pipe)
{
	if (args.io[0] != STDIN_FILENO)
	{
		if (dup2(args.io[0], STDIN_FILENO) < 0)
			perror("dup2");
	}
	if (args.io[1] != STDOUT_FILENO)
	{
		if (dup2(args.io[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
		if (close(pipe[0]))
			perror("close");
		if (close(pipe[1]))
			perror("close");
}

void	run_cmds(t_arg *args, t_list *envll)
{
	int		exit_status;
	int		cfd[2];
	pid_t	pid;
	pid_t	*cids;

	if (args[0].last)
		run_single(args, list_to_array(envll), envll);
	else
	{
		if (pipe(cfd) < 0)
			perror("pipe");
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			close(cfd[0]);
			signal(SIGINT, sigint_child);
			signal(SIGQUIT, SIG_DFL);
			minishell_piping(args, envll, cfd[1]);
		}
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, SIG_IGN);
		cids = read_cids(args, cfd);
		for (int i = 0; i < 2; i++)
			ft_printf_fd(2, "%d\n", cids[i]);
		exit_status = wait_cids(args, cids);
		(void)exit_status;
		signal(SIGINT, sigint_parent);
		signal(SIGQUIT, SIG_DFL);
		//ft_free_split(&envp);
		//set errno from exitstatus;
	}
}

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
