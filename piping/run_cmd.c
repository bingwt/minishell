/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:18:24 by xlow              #+#    #+#             */
/*   Updated: 2024/03/13 03:06:54 by xlow             ###   ########.fr       */
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
		//*io = fd[0];
		if (dup2(fd[0], *io) < 0)
		{
			perror("Dup2");
			exit(1);
		}
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
			//args.io[0] = open(args.in[i], O_RDONLY);
			dup2(open(args.in[i], O_RDONLY), args.io[0]);
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
			dup2(open(args.out[i++], APPEND, 0644), args.io[1]);
			//args.io[1] = open(args.out[i++], APPEND, 0644);
		else
			dup2(open(args.out[i++], TRUNC, 0644), args.io[1]);
			//args.io[1] = open(args.out[i++], TRUNC, 0644);
		if (args.io[1] == -1)
			perror("open");
	}
	return (args);
}
/*
char	*get_path(char *cmd, t_list *envll)
{
	char	*temp;
	char	*program_path;
	char	**path;
	char	**ptr;
	char	*program;

	//path = ft_split(getenv("PATH"), ':');
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
*/
void	execute(t_arg *args, char **envp, t_list *envll, int i)
{
	char	*path;

	args[i] = open_files(args[i]);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
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

void	run_cmds(t_arg *args, t_list *envll, char **envp, int i)
{
	int		fd[2];
	int		exit_status;
	pid_t	pid;

	if (pipe(fd) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("minibing");
	if (!pid)
	{
		if (!args[0].last)
		{
			args[i].io[0] = fd[0];
			args[i].io[1] = args[i].p_out;
		}
		execute(args, envp, envll, i);
	}
	waitpid(pid, &exit_status, 0);
	if (!args[i].last)
	{
		close(fd[0]);
		args[i + 1].p_out = fd[1];
		run_cmds(args, envll, envp, i + 1);
	}
}
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
