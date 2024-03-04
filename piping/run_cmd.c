#include "minishell.h"

int	builtin_table(t_arg args, char **envp, t_list *envll)
{
	char	*cmd;

	cmd = args.cmd[0];
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(args);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(args);
	else if (!ft_strcmp(cmd, "pwd"))
		printf("%s\n", ft_pwd());
	else if (!ft_strcmp(cmd, "export"))
		ft_export(args, &envll);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(args, &envll);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(envp);
	else if (!ft_strcmp(cmd, "minibing"))
		minibing();
	else if (!ft_strcmp("exit", cmd))
		exit(0);
	else
		return (0);
	return (1);
}

t_arg	open_files(t_arg args)
{
	int	i;

	i = 0;
	while (i <= args.in_i)
	{
		if (!ft_strcmp(args.in[i++], "<"))
			args.io[0] = open(args.in[i], O_RDONLY);
		else
			args.io[0] = heredoc implementation;
		if (args.io[0] == -1)
			error with exit, failed open == cmd not executed;
		i++;
	}
	i = 0;
	while (i <= args.out_i)
	{
		if (!ft_strcmp(args.out[i++], ">>"))
			args.io[1] = open(args.out[i++], APPEND, 0644);
		else
			args.io[1] = open(args.out[i++], TRUNC, 0644);
		if (args.io[1] == -1)
			error with exit;
	}
	return (args);
}

void	dup_pipes(t_arg args, int *pipe)
{
}

void	run_single(t_arg *args, char **envp, t_list *envll)
{
	char	*path;
	pid_t	pid;

	args[0] = open_files(args[0]);
	if (!args[0].cmd[0])
		return ;
	if (dup2(args[0].io[0], 0) < 0 || dup2(args[0].io[1], 1) < 0)
		perror("dup2"), return ;
	if (builtin_table(args[0], envp, envll))
		return ;
	pid = fork();
	if (pid < 0)
		perror("fork"), return ;
	if (!pid)
	{
		if (!access(args[0].cmd[0], X_OK))
			execve(args[0].cmd[0], args[0].cmd, envp);
		path = get_path(args[0].cmd[0]);
		if (!path)
			perror("path"), exit(1) ;
		execve(path, args[0].cmd, envp);
		perror("execve"), free_args(args), exit(1) ;
	}
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
			perror("fork"), return ;
		if (!pid)
			minishell_piping(args, envp, envll);
		waitpid(pid, &exit_status, WNOHANG);
		fancy schmancy errno function;
	}
}
