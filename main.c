/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 02:40:25 by btan              #+#    #+#             */
/*   Updated: 2024/04/10 02:40:32 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minibing(t_list **envll)
{
	char	*prompt;
	char	*buffer;
	t_arg	*args;

	prompt = init_prompt(*envll);
	buffer = readline(prompt);
	free(prompt);
	if (buffer && *buffer)
		add_history(buffer);
	if (!buffer)
	{
		printf("exit\n");
		return (0);
	}
	prompt = expand_env(buffer, *envll);
	args = input_parser(prompt);
	if (args)
		run_cmds(args, envll);
	if (args)
		free_args(args);
	free(buffer);
	free(prompt);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int		io[2];
	t_list	*envll;

	(void) argc, (void) argv;
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
	envll = NULL;
	array_to_list(&envll, envp);
	set_shlvl(&envll);
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	while (1)
	{
		dup2(io[0], STDIN_FILENO);
		dup2(io[1], STDOUT_FILENO);
		if (!minibing(&envll))
			break ;
	}
	ft_lstclear(&envll, free);
	return (0);
}
