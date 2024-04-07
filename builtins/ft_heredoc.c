/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:23:35 by btan              #+#    #+#             */
/*   Updated: 2024/04/07 15:39:04 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc(int sig)
{
	close(0);
	write(1, "\n", 1);
	get_exit_status(unshift_exitcode(130));
	signal(sig, sigint_parent);
}

void	ft_heredoc(char	*eof, int fd)
{
	char	*buffer;

	signal(SIGINT, sigint_heredoc);
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!buffer || !ft_strcmp(buffer, eof))
		{
			signal(SIGINT, sigint_parent);
			return ;
		}
		if (fd >= 0)
		{
			write(fd, buffer, ft_strlen(buffer));
			write(fd, "\n", 1);
		}
		free(buffer);
	}
	signal(SIGINT, sigint_parent);
}
//
//int	main(int argc, char **argv)
//{
//	int		p_fd[2];
//	char	*buffer;
//
//	pipe(p_fd);
//	ft_heredoc_wo_pipe(argv[1], p_fd);
//	close(p_fd[1]);
//	buffer = ft_calloc(PIPE_BUF + 1, sizeof(char));
//	while (read(p_fd[0], buffer, PIPE_BUF) > 0);
//	printf("%s", buffer);
//	free(buffer);
//	close(p_fd[0]);
//
////	ft_heredoc_w_pipe(argv[1]);
//}
