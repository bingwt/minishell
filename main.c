/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 22:16:20 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*prompt;
	char	*buffer;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = init_prompt();
		if (argc == 2)
		{
			printf("%s mode\n", argv[1]);
			buffer = readline("minibing> ");
		}
		else
			buffer = readline(prompt);
		free(prompt);
		if (buffer && *buffer)
			add_history(buffer);
		if (!buffer)
		{
			printf("exit\n");
			break ;
		}
		run_cmd(buffer);
		free(buffer);
	}
	return (0);
}
