/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:49:52 by btan              #+#    #+#             */
/*   Updated: 2024/04/11 10:05:44 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_parent(int sig)
{
	(void) sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	get_exit_status(unshift_exitcode(130));
}

int	sig_handler(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	signal(SIGINT, sigint_parent);
	if (WIFSIGNALED(status))
	{
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			get_exit_status(unshift_exitcode(130));
		}
		if (sig == SIGQUIT)
		{
			write(1, "Quit\n", 5);
			get_exit_status(unshift_exitcode(131));
		}
		return (0);
	}
	return (1);
}
