/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/03/08 12:21:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		io[2];
	char	*prompt;
	char	*buffer;
	t_arg	*args;
	t_list	*envll;

	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
	envll = NULL;
	array_to_list(&envll, envp);
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
//	expand_env("This is $HOME, truly", envll);
//	ft_export("export test=something", &envll);
//	ft_export("export test=somethingelse", &envll);
//	ft_unset("unset test", &envll);
	ft_export(ft_strjoin("export SHLVL=", \
	ft_itoa(ft_atoi(expand_env("$SHLVL", envll)) + 1)), &envll);
	while (1)
	{
		prompt = init_prompt(envll);
		if (dup2(io[0], STDIN_FILENO) < 0 || dup2(io[1], STDOUT_FILENO) < 0)
				perror("Dup");
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
		args = input_parser(buffer);
		run_cmds(args, envp, envll);
		free(buffer);
	}
	ft_lstclear(&envll, free);
//	free(envp);
	return (0);
}
