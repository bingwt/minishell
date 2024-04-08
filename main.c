/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/04/08 22:26:25 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**test_args;

	test_args = ft_calloc(4, sizeof(char *));
	test_args[0] = "export";
	int		io[2];
	char	*prompt;
	char	*buffer;
	t_arg	*args;
	t_list	*envll;

//	signal(SIGINT, sigint_parent);
//	signal(SIGQUIT, SIG_IGN);
	sighandler_parent();
	envll = NULL;
	array_to_list(&envll, envp);
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	// expand_all("echo '$HOME' \"$HOME\"", envll);
	// expand_all("echo $wfsa", envll);
	//expand_env("echo $HOME", envll);
	// test_args[1] = "test=something";
	// test_args[2] = "test2=somethingelse";
//	test_args[1] = "test=something";
//	ft_export(test_args, &envll);
//	test_args[0] = "unset";
//	test_args[1] = "test";
//	ft_unset(test_args, &envll);
	set_shlvl(&envll);
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
		prompt = expand_env(buffer, envll);
		args = input_parser(prompt);
		if (args)
			run_cmds(args, &envll);
		if (args)
			free_args(args);
		free(buffer);
	}
	ft_lstclear(&envll, free);
	return (0);
}
