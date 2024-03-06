/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:23:35 by btan              #+#    #+#             */
/*   Updated: 2024/03/05 16:01:41 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc_w_pipe(char	*eof)
{
	int		p_fd[2];
	char	*buffer;

	pipe(p_fd);
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!strcmp(buffer, eof))
			return ;
		write(p_fd[1], buffer, ft_strlen(buffer));
		write(p_fd[1], "\n", 1);
		free(buffer);
	}
	close(p_fd[1]);
	buffer = ft_calloc(PIPE_BUF + 1, sizeof(char));
	while (read(p_fd[0], buffer, PIPE_BUF) > 0);
	printf("%s", buffer);
	free(buffer);
	close(p_fd[0]);
}

void	ft_heredoc(char	*eof, int fd)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (!strcmp(buffer, eof))
			return ;
		if (fd >= 0)
		{
			write(fd, buffer, ft_strlen(buffer));
			write(fd, "\n", 1);
		}
		free(buffer);
	}
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