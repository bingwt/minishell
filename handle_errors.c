/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:51:59 by btan              #+#    #+#             */
/*   Updated: 2024/04/02 15:57:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_status(t_errors error)
{
	if (error == NOT_VALID_ID || error == TOO_MANY_ARGS)
		return (1);
	if (error == UNCLOSED_QUOTES || error == INVALID_EXIT \
		|| error == UNEXPECTED_TOKEN || error == CMD_NOT_FOUND)
		return (2);
	if (error == NO_PERMS || error == IS_DIR)
		return (126);
	if (error == CMD_NOT_FOUND || error == NO_FILE)
		return (127);
	return (0);
}

int	handle_error(char *vars, t_errors error)
{
	int	status;

	status = handle_status(error);
	printf("Error: %d: %s\n", error, vars);
	if (error == NOT_VALID_ID)
		status = 1;
	get_exit_status(unshift_exitcode(status));
//	ft_putstr_fd("minibing: ", 2);
//	if (!vars)
//	{}
//	ft_putchar_fd('\n', 2);
	return (status);
}

int	get_exit_status(int status)
{
	static int	exit_status;

	if (status == -1)
		return (exit_status);
	exit_status = WEXITSTATUS(status);
	return (exit_status);
}

int	unshift_exitcode(int status)
{
	return ((status | 0xff00) << 8);
}
