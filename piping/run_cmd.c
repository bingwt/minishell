#include "../minishell.h"
#include "mspiping.h"

int	builtin_table(t_arg args, t_list *envll)
{
	char	*cmd;

	cmd = ft_strjoin_strs(args.cmd);
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
		return (0);
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
	//if (close(args.io[0]) || close(args.io[1]))
	//	perror("dup2");
	if (args.io[0] != pipe[0])
		if (close(pipe[0]))
			perror("dup2");
	if (args.io[1] != pipe[1])
		if (close(pipe[1]))
			perror("dup2");
}

void	run_cmds(t_arg *args, char **envp, t_list *envll)
{
	int		exit_status;
	pid_t	pid;

	if (args[0].last)
		run_single(args, envp, envll);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (!pid)
			minishell_piping(args, envp, envll);
		waitpid(pid, &exit_status, WNOHANG);
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
	run_cmds(args, envp, envll);
	return (0);
}