/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:49:52 by btan              #+#    #+#             */
/*   Updated: 2024/04/10 19:23:01 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	(void) sig;
	//printf("sig: %d\n", sig);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	get_exit_status(unshift_exitcode(130));
}

void	sigint_parent(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	get_exit_status(unshift_exitcode(130));
	signal(sig, sigint_parent);
}

void	sigint_child(int sig)
{
	(void) sig;
	signal(SIGINT, SIG_DFL);
	write(1, "\n", 1);
}

void	sigquit_child(int sig)
{
	(void) sig;
	signal(SIGQUIT, SIG_DFL);
	write(2, "Quit\n", 5);
	get_exit_status(unshift_exitcode(131));
//	signal(sig, SIG_DFL);
}

void	sighandler_child(void)
{
	signal(SIGINT, sigint_child);
//	signal(SIGQUIT, sigquit_child);
	signal(SIGQUIT, SIG_DFL);
}

void	sighandler_wait(void)
{
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigquit_child);
}

void	sig_wait(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		printf("Quit\n");
	signal(sig, SIG_IGN);
}

void	sighandler_parent(void)
{
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
}
