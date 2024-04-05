/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:49:52 by btan              #+#    #+#             */
/*   Updated: 2024/04/05 12:54:58 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("child?\n");
	write(1, "\n", 1);
	get_exit_status(unshift_exitcode(130));
	signal(sig, sigint_parent);
}

void	sigquit_child(int sig)
{
	write(2, "Quit (core dumped)", 18);
	write(1, "\n", 1);
	get_exit_status(unshift_exitcode(131));
	signal(sig, SIG_DFL);
}

void	sighandler_child(void)
{
	printf("sig_child\n");
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigquit_child);
}

void	sighandler_wait(void)
{
	printf("sig_wait\n");
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigquit_child);

}

void	sighandler_parent(void)
{
	printf("sig_parent\n");
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	sighandler_heredoc(void)
{
	printf("sig_heredoc\n");
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, SIG_IGN);
}
