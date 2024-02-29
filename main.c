/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/02/29 21:43:05 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*buffer;
//	char	**envp;
	t_list	*envll;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	envll = NULL;
	array_to_list(&envll, envp);
//	expand_env("This is $HOME, truly", envll);
//	ft_export("export test=something", &envll);
//	ft_export("export test=somethingelse", &envll);
//	ft_unset("unset test", &envll);
	while (1)
	{
		prompt = init_prompt(envll);
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
		run_cmd(buffer, envll);
		free(buffer);
	}
	ft_lstclear(&envll, free);
//	free(envp);
	return (0);
}
