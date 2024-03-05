/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:00:32 by btan              #+#    #+#             */
/*   Updated: 2024/03/05 14:25:44 by btan             ###   ########.fr       */
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

static int	builtin_table(char *cmd, t_list *envll)
{
	if (!ft_strncmp("echo ", cmd, 5))
		ft_echo(cmd + 5);
	else if (!ft_strncmp("cd ", cmd, 3))
		ft_cd(cmd + 3, envll);
	else if (!ft_strncmp("pwd ", cmd, 4))
		printf("%s\n", ft_pwd());
	else if (ft_strnstr(cmd, "export", 7))
		ft_export(cmd, &envll);
	else if (ft_strnstr(cmd, "unset", 6))
		ft_unset(cmd, &envll);
	else if (!ft_strncmp("env ", cmd, 4))
		ft_env(envll);
	else if (!ft_strncmp("expand $", cmd, 8))
	{
		printf("Raw: %s\n", cmd);
		printf("Expanded: %s\n", expand_env(cmd, envll));
	}
	else if (!ft_strncmp("minibing", cmd, 8))
		minibing();
	else if (!ft_strncmp("status ", cmd, 7))
		printf("Exit Status is %d\n", get_exit_status(ft_atoi(cmd + 7)));
	else if (!ft_strncmp("exit", cmd, 4))
	{
		ft_lstclear(&envll, free);
		if (!ft_strncmp("exit ", cmd, 5))
			ft_exit(ft_atoi(cmd + 5));
		ft_exit(0);
	}
	else
		return (0);
	return (1);
}

void	run_cmd(char *cmd, t_list *envll)
{
	char	**envp;
	char	**args;
	char	*path;
	pid_t	pid;
	int		status;

	if (!*cmd)
		return ;
	cmd = expand_env(cmd, envll);
	if (builtin_table(cmd, envll))
		return ;
	envp = list_to_array(envll);
	args = ft_split(cmd, ' ');
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!access(args[0], X_OK))
			execve(args[0], args, envp);
		path = get_path(args[0], envll);
		if (!path)
		{
			handle_error(args[0], "CMD_NOT_FOUND");
			free_strs(args);
			free(path);
			free(envp);
			exit(127);
		}
		execve(path, args, envp);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_free_split(&args);
	free(envp);
	waitpid(pid, &status, 0);
	get_exit_status(status);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
