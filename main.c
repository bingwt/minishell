/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/02/28 16:52:39 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*prompt;
	char	*buffer;
	char	**envp;
	t_list	*envll;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	envll = NULL;
	init_envll(&envll);
	envp = list_to_array(envll);
//	expand_env("This is $HOME, truly", envll);
//	ft_export("export test=something", &envll);
//	ft_export("export test=somethingelse", &envll);
//	ft_unset("unset test", &envll);
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
		run_cmd(buffer, &envp, envll);
		free(buffer);
	}
	ft_lstclear(&envll, free);
	free(envp);
	return (0);
}
