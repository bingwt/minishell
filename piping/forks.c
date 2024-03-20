/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:24:27 by xlow              #+#    #+#             */
/*   Updated: 2024/03/18 21:33:29 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *cmd, t_list *envll)
{
	char	*temp;
	char	*program_path;
	char	**path;
	char	**ptr;
	char	*program;

	temp = expand_env("$PATH", envll);
	path = ft_split(temp, ':');
	free(temp);
	ptr = path;
	program = ft_strjoin("/", cmd);
	while (*ptr)
	{
		program_path = ft_strjoin(*(ptr++), program);
		if (!access(program_path, X_OK))
			break ;
		free(program_path);
		program_path = NULL;
	}
	free(program);
	ft_free_split(&path);
	return (program_path);

}

static void	execute(t_arg *args, char **envp, t_list *envll, int i)
{
	char	*path;

	if (!args[i].cmd[0])
		exit(0);
	if (builtin_table(args[i], envll))
		exit(0);
	if (!access(args[i].cmd[0], X_OK))
		execve(args[i].cmd[0], args[i].cmd, envp);
	path = get_path(args[i].cmd[0], envll);
	if (!path)
	{
		handle_error(args[i].cmd[0], "CMD_NOT_FOUND");
		free_args(args);
		exit(127);
	}
	execve(path, args[i].cmd, envp);
	free_args(args);
	ft_free_split(&envp);
	perror("execve");
	exit(1);
}

void	run_single(t_arg *args, t_list *envll)
{
	pid_t	pid;
	int		status;

	args[0] = open_files(args[0], NULL);
	dup2(args[0].io[0], 0);
	dup2(args[0].io[1], 1);
	if (builtin_table(args[0], envll))
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, SIG_DFL);
		execute(args, list_to_array(envll), envll, 0);
	}
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	get_exit_status(status);
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_DFL);
}

static void	iterative_body(t_arg *args, t_list *envll, int *hd_fd)
{
	int		i;
	int		new_fd[3];
	pid_t	pid;

	i = 0;
	new_fd[2] = dup(0);
	while (1)
	{
		pipe(new_fd);
		pid = fork();
		if (!pid)
		{
			args = child_dup(args, new_fd, i, hd_fd);
			execute(args, list_to_array(envll), envll, i);
		}
		else
		{
			dup2(new_fd[0], new_fd[2]);
			close(new_fd[0]);
			close(new_fd[1]);
			if (args[i].last)
				break ;
		}
		i++;
	}
}

void	iterative_piping(t_arg *args, t_list *envll)
{
	int		hd_fd[2];
	int		exit_status;

	exit_status = 0;
	pipe(hd_fd);
	iterative_body(args, envll, hd_fd);
	while (waitpid(-1, &exit_status, 0) != -1)
		;
	exit(exit_status);
}
/*
static void	recursive_piping(t_arg *args, t_list *envll, int *fd, int cfd)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (!args[i].last)
		i++;
	if (i)
		args[i - 1].last = 1;
	if (close(fd[0]))
		perror("close");
	args[i].io[1] = fd[1];
	if (pipe(fd) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (!pid && !i)
	{
		close(fd[0]), close(fd[1]);
		close(cfd);
		exit(0);
	}
	if (!pid)
		recursive_piping(args, envll, fd, cfd);
	write_cid(pid, cfd);
	if (i)
		args[i].io[0] = fd[0];
	args[i] = open_files(args[i]);
	dup_pipes(args[i], fd);
	close(args[i].io[1]);
	waitpid(pid, NULL, 0);
	parent_pipe(args, list_to_array(envll), envll, i);
}

void minishell_piping(t_arg *args, t_list *envll, int cfd)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = 0;
	while (!args[i].last)
		i++;
	args[i - 1].last = 1;
	if (pipe(fd) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (!pid)
		recursive_piping(args, envll, fd, cfd);
	write_cid(pid, cfd);
	args[i].io[0] = fd[0];
	args[i] = open_files(args[i]);
	dup_pipes(args[i], fd);
	waitpid(pid, NULL, 0);
	parent_pipe(args, list_to_array(envll), envll, i);
}
*/
