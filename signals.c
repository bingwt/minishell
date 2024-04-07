/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:49:52 by btan              #+#    #+#             */
/*   Updated: 2024/03/16 11:58:53 by btan             ###   ########.fr       */
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
	write(1, "\n", 1);
	get_exit_status(unshift_exitcode(130));
	signal(sig, sigint_parent);
}

void	sighandler_child(void)
{
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, SIG_DFL);
}

void	sighandler_wait(void)
{
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, SIG_IGN);
}

void	sighandler_parent(void)
{
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
}
