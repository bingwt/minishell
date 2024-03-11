/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:51:59 by btan              #+#    #+#             */
/*   Updated: 2024/03/05 14:17:48 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(char *vars, char *error)
{
	ft_putstr_fd("minibing: ", 2);
	if (!ft_strncmp(error, "CMD_NOT_FOUND", 13))
	{
		ft_printf_fd(2, "command not found: %s\n", vars);
		return (127);
	}
	if (!ft_strncmp(error, "NO_FILE", 7))
		ft_putstr_fd("no such file or directory: ", 2);
	if (!ft_strncmp(error, "NO_PERMS", 8))
		ft_putstr_fd("permission denied: ", 2);
	ft_putstr_fd(vars, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
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
	return((status | 0xff00) << 8);
}
