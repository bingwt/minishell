/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:49:52 by btan              #+#    #+#             */
/*   Updated: 2024/02/09 22:21:11 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signal)
{
	//printf("Signal: %d\n", signal);
	if (signal == 242 || signal == SIGINT)
	{
		printf("\n");
		prompt();
	}
	if (signal == SIGQUIT)
		prompt();
}
