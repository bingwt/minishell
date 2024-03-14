#include "minishell.h"

void	run_single(t_arg *args, char **envp, t_list *envll)
{
	char	*path;
	pid_t	pid;
	int		status;

	args[0] = open_files(args[0]);
	//if (!args[0].cmd[0])
	//	return ;
	if (dup2(args[0].io[0], 0) < 0 || dup2(args[0].io[1], 1) < 0)
	{
		perror("dup2");
		return ;
	}
	if (builtin_table(args[0], envll))
		return ;
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
		if (!access(args[0].cmd[0], X_OK))
			execve(args[0].cmd[0], args[0].cmd, envp);
		path = get_path(args[0].cmd[0], envll);
		if (!path)
		{
			//perror("path"), exit(1) ;
			handle_error(args[0].cmd[0], "CMD_NOT_FOUND");
			exit(127);
		}
		execve(path, args[0].cmd, envp);
		perror("execve"), free_args(args), exit(1) ;
	}
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	get_exit_status(status);
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_DFL);
}

static void	parent_pipe(t_arg *args, char **envp, t_list *envll, int i)
{
	char	*path;

	if (builtin_table(args[i], envll))
		exit(0);
	if (!access(args[i].cmd[0], X_OK))
		execve(args[i].cmd[0], args[i].cmd, envp);
	path = get_path(args[i].cmd[0], envll);
	if (!path)
	{
		free_args(args);
		//free envll;
		perror("cmd not found");
		exit(127);
	}
	execve(path, args[i].cmd, envp);
	free_args(args);
	ft_free_split(&envp);
	//free envll
	perror("execve");
	exit(1); // error code
}

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
	parent_pipe(args, list_to_array(envll), envll, i);
}
