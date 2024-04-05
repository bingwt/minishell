/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:18:24 by xlow              #+#    #+#             */
/*   Updated: 2024/04/05 13:11:39 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 int	exebuns(char *cmd, char **args, t_list **envll)
 {
	 if (!cmd)
		 return (0);
	 if (!strcmp(cmd, "echo"))
		 ft_echo(args);
	 else if (!strcmp(cmd, "cd"))
		 ft_cd(args, *envll);
	 else if (!strcmp(cmd, "pwd"))
		 printf("%s\n", ft_pwd());
	 else if (!strcmp(cmd, "export"))
		 ft_export(args, envll);
	 else if (!strcmp(cmd, "unset"))
		 ft_unset(args, envll);
	 else if (!strcmp(cmd, "env"))
		 ft_env(*envll);
	 else if (!strcmp(cmd, "exit"))
		 ft_exit(args);
// 	 else if (rabbithole(cmd, args, envll))
// 	 	return (1);
 	else
 		return (0);
 	return (1);
 }

//int	builtin_table(t_arg args, t_list *envll)
//{
//	char	*cmd;
//
//	cmd = ft_strsjoin(args.cmd);
//	if (!ft_strcmp(args.cmd[0], "echo"))
//		ft_echo(args.cmd);
//	else if (!ft_strcmp(args.cmd[0], "cd"))
//		ft_cd(args.cmd, envll);
//	else if (!ft_strcmp(args.cmd[0], "pwd"))
//		printf("%s\n", ft_pwd());
//	else if (!ft_strcmp(args.cmd[0], "export"))
//		ft_export(args.cmd, &envll);
//	else if (!ft_strcmp(args.cmd[0], "unset"))
//		ft_unset(args.cmd, &envll);
//	else if (!ft_strcmp(args.cmd[0], "env"))
//		ft_env(envll);
//	else if (!ft_strcmp("exit", args.cmd[0]))
//		ft_exit(args.cmd);
//	//	{
//	//		ft_lstclear(&envll, free);
//	//		if (ft_strlen(cmd) > 4)
//	//			ft_exit(cmd + 4);
//	//		ft_exit(0);
//	//	}
//	else
//	{
//		free(cmd);
//		return (0);
//	}
//	free(cmd);
//	return (1);
//}

static t_arg	heredoc_queue(t_arg args, int *hd_fd)
{
	char	*temp;

	temp = NULL;
	while (1)
	{
		temp = get_next_line(hd_fd[0]);
		if (temp)
		{
			free(temp);
			temp = NULL;
			args.heredoc = 0;
			break ;
		}
	}
	return (args);
}

t_arg	open_heredoc(t_arg args, int i, int *hd_fd)
{
	int		fd[2];

	if (hd_fd && args.heredoc)
		args = heredoc_queue(args, hd_fd);
	if (i == args.in_i - 2)
	{
		pipe(fd);
		dup2(fd[0], args.io[0]);
		ft_heredoc(args.in[i], fd[1]);
		close(fd[1]);
		if (hd_fd)
			write(hd_fd[1], "\n", 1);
	}
	else
		ft_heredoc(args.in[i], -1);
	return (args);
}

t_arg	open_files(t_arg args, int *hd_fd)
{
	int	cock;
	int	i;

	i = 0;
	while (i < args.in_i - 1)
	{
		if (!ft_strcmp(args.in[i++], "<"))
		{
			cock = open(args.in[i++], O_RDONLY);
			if (cock == -1)
			{
				//perror("shit");
				handle_error(args.in[i - 1], NO_PERMS);
				args.io[0] = -1;
				return (args);
			}
			else
				dup2(cock, args.io[0]);
		}
		else
			args = open_heredoc(args, i++, hd_fd);
	}
	i = 0;
	while (i < args.out_i - 1)
	{
		if (!ft_strcmp(args.out[i++], ">>"))
		{
			cock = open(args.out[i++], APPEND, 0644);
			if (cock < -1)
			{
				//perror("shit");
				handle_error(args.out[i - 1], NO_PERMS);
				args.io[1] = -1;
				return (args);
			}
			else
				dup2(cock, args.io[1]);
		}
		else
		{
			cock = open(args.out[i++], TRUNC, 0644);
			if (cock == -1)
			{
				//perror("shit");
				handle_error(args.out[i - 1], NO_PERMS);
				args.io[1] = -1;
				return (args);
			}
			else
				dup2(cock, args.io[1]);
		}
	}
	return (args);
}

void	run_cmds(t_arg *args, t_list **envll)
{
	int		exit_status;
	pid_t	pid;

	if (args[0].last)
		run_single(args, envll);
	else
	{
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
			iterative_piping(args, envll);
		}
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &exit_status, 0);
		signal(SIGINT, sigint_parent);
		signal(SIGQUIT, SIG_DFL);
	}
}
