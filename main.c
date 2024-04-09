/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 02:40:25 by btan              #+#    #+#             */
/*   Updated: 2024/04/10 03:43:39 by btan             ###   ########.fr       */
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
	free(prompt);
	if (args)
		run_cmds(args, envll);
	if (args)
		free_args(args);
	free(buffer);
	return (1);
}

void	sig_handler(int sig)
{
	(void) sig;
	//printf("sig: %d\n", sig);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	s_sa;
	int		io[2];
	t_list	*envll;

	(void) argc, (void) argv;
	ft_memset(&s_sa, 0, sizeof(s_sa));
	s_sa.sa_handler = sig_handler;
	sigaction(SIGINT, &s_sa, NULL);
	//signal(SIGINT, sigint_parent);
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
