/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:00:32 by btan              #+#    #+#             */
/*   Updated: 2024/02/28 15:31:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **strs)
{
	char	**temp;

	temp = strs;
	while (*strs)
		free(*(strs++));
	free(temp);
}

char	*get_path(char *cmd)
{
	char	*program_path;
	char	**path;
	char	**ptr;
	char	*program;

	path = ft_split(getenv("PATH"), ':');
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

int	handle_error(char *vars, char *error)
{
	ft_putstr_fd("minibing: ", 2);
	if (!ft_strncmp(error, "CMD_NOT_FOUND", 13))
	{
		ft_printf_fd(2, "command not found: %s\n", vars);
		return (127);
	}
	if (!ft_strncmp(error, "NO_FILE", 7))
		ft_putstr_fd("no such file or directory: ", 2);
	if (!ft_strncmp(error, "NO_PERMS", 8))
		ft_putstr_fd("permission denied: ", 2);
	ft_putstr_fd(vars, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

//void	run_cmd(char *cmd)
//{
//	printf("%s\n", get_path(cmd));
//	char	**args;
//	char	*path;
//	pid_t	pid;
//
//	args = ft_split(cmd, ' ');
//	path = get_path(args[0]);
//	pid = fork();
//	if (pid == 0)
//	{
//		if (!access(path, X_OK))
//			execve(cmd, args, NULL);
//		execve(path, args, NULL);
//	}
//}

//	proposed run_cmd with routing table

static int	builtin_table(char *cmd, char **envp, t_list *envll)
{
	if (!ft_strncmp("echo ", cmd, 5))
		ft_echo(cmd + 5);
	else if (!ft_strncmp("cd ", cmd, 3))
		ft_cd(cmd + 3);
	else if (!ft_strncmp("pwd ", cmd, 4))
		printf("%s\n", ft_pwd());
	else if (ft_strnstr(cmd, "export", 7))
		ft_export(cmd, &envll);
	else if (ft_strnstr(cmd, "unset", 6))
		ft_unset(cmd, &envll);
	else if (!ft_strncmp("env ", cmd, 4))
		ft_env(envp);
	else if (!ft_strncmp("expand $", cmd, 8))
	{
		printf("Raw: %s\n", cmd);
		printf("Expanded: %s\n", expand_env(cmd, envll));
	}
	else if (!ft_strncmp("minibing", cmd, 8))
		minibing();
	else if (!ft_strcmp("exit", cmd))
		exit(0);
	else
		return (0);
	return (1);
}

void	run_cmd(char *cmd, char ***envp, t_list *envll)
{
	char	**args;
	char	*path;
	pid_t	pid;

	if (!*cmd)
		return ;
	cmd = expand_env(cmd, envll);
	if (builtin_table(cmd, *envp, envll))
		return ;
	args = ft_split(cmd, ' ');
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!access(args[0], X_OK))
			execve(args[0], args, *envp);
		path = get_path(args[0]);
		if (!path)
		{
			handle_error(args[0], "CMD_NOT_FOUND");
			free_strs(args);
			free(path);
			exit(127);
		}
		execve(path, args, *envp);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_free_split(&args);
	waitpid(pid, NULL, 0);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
