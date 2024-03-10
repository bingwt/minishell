/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/03/08 16:30:34 by btan             ###   ########.fr       */
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
	ft_export(ft_strjoin("exportSHLVL=", \
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
		prompt = expand_env(buffer, envll);
		args = input_parser(prompt);
		if (args)
			run_cmds(args, envll);
		if (args)
			free_args(args);
		free(buffer);
	}
	ft_lstclear(&envll, free);
	return (0);
}
