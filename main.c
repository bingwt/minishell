/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/02/09 22:26:35 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*buffer;
	char		*temp;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt();
		buffer = readline(0);
		if (!buffer)
		{
			printf("exit\n");
			break ;
		}
		if (!strncmp("echo", buffer, 4))
			ft_echo(buffer + 5);
		if (!strncmp("cd", buffer, 2))
			ft_cd(buffer + 3);
		if (!strncmp("pwd", buffer, 3))
		{
			temp = ft_pwd();
			printf("%s\n", temp);
			free(temp);
		}
		if (!strncmp("exit", buffer, 4))
			exit(0);
		free(buffer);
	}
	return (0);
}
