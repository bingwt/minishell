/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:00:32 by btan              #+#    #+#             */
/*   Updated: 2024/02/20 16:32:58 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	free_strs(char **strs)
{
	char	**temp;

	temp = strs;
	while (*strs)
		free(*(strs++));
	free(temp);
}*/

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

int	builtin_table(char *cmd)
{
	if (!ft_strncmp("echo ", cmd, 5))
		ft_echo(cmd + 5);
	else if (!ft_strncmp("cd ", cmd, 3))
		ft_cd(cmd + 3);
	else if (!ft_strncmp("pwd ", cmd, 4))
		printf("%s\n", ft_pwd());
	else if (!ft_strcmp("exit", cmd))
		exit(0);
	else
		return (0);
	return (1);
}

void	run_cmd(char *cmd)
{
	char	**args;
	char	*path;
	pid_t	pid;

	if (builtin_table(cmd))
		return ;
	args = ft_split(cmd, ' ');
	pid = fork();
	if (!pid)
	{
		if (!access(args[0], X_OK))
			execve(args[0], args, NULL);
		path = get_path(cmd);
		execve(path, args, NULL);
	}
	waitpid(pid, NULL, WNOHANG);
}
