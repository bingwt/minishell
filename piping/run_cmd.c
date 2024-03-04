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
			args.io[0] = open(args.in[i++], O_RDONLY);
		else
			args.io[0] = heredoc implementation;
		if (args.io[0] == -1)
			error with exit, failed open == cmd not executed;
	}
	i = 1;
	while (i <= args.out_i)
	{
		if (!ft_strcmp(args.in[args.in_i - 1], "<<"))
			args.io[1] = open(args.out[i], APPEND, 0644);
		else
			args.io[1] = open(args.out[i], TRUNC, 0644);
		i += 2;
		if (args.io[1] == -1)
			error with exit;
	}
	return (args);
}

void	dup_pipes(t_arg args, int *pipe)
{
}

void	run_single(t_arg args, char **envp, t_list *envll)
{
	int		std[2];
	char	*path;
	// i am destroying stdin and stdout every time i do this
	// but im hoping that because everything runs through here
	// it would reset every time before we get to anything
	// that could possibly break
	args = open_files(args);
	if (!args.cmd[0])
		return ;
	if (dup2(args.io[0], 0) < 0 || dup2(args.io[1], 1) < 0)
		perror("dup2"), return ;
	if (builtin_table(args, envp, envll))
		return ;
	if (!access(args.cmd[0], X_OK))
		execve(args.cmd[0], args.cmd, envp);
	path = get_path(args.cmd[0]);
	if (!path)
		perror(path), return ;
	execve(path, args.cmd, *envp);
	perror(execve), return ;
}

void	run_cmds(t_arg *args, char **envp, t_list *envll)
{
	if (args[0].last)
		run_single(args[0], envp, envll);
