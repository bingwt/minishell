/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:27:32 by btan              #+#    #+#             */
/*   Updated: 2024/03/13 02:55:19 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*buffer;
	t_arg	*args;
	t_list	*envll;

	(void)argv;
	if (argc != 1)
		handle_error(NULL, "Too many args");
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
	envll = NULL;
	array_to_list(&envll, envp);
	ft_export(ft_strjoin("exportSHLVL=", \
	ft_itoa(ft_atoi(expand_env("$SHLVL", envll)) + 1)), &envll);
	while (1)
	{
		prompt = init_prompt(envll);
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
		free(prompt);
		if (args)
			run_cmds(args, envll, list_to_array(envll), 0);
		if (args)
			free_args(args);
		//free(buffer);
	}
	ft_lstclear(&envll, free);
	return (0);
}
