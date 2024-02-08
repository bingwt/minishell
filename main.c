/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/02/08 22:25:36 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*buffer;

	while (1)
	{
		printf("minibing> ");
		buffer = readline(0);
		if (!strncmp("echo", buffer, 4))
			ft_echo(buffer + 5);
		if (!strncmp("cd", buffer, 2))
			ft_cd(buffer + 3);
		if (!strncmp("pwd", buffer, 3))
			ft_pwd();
		if (!strncmp("exit", buffer, 4))
			exit(0);
	}
	return (0);
}
