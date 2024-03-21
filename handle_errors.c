/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:51:59 by btan              #+#    #+#             */
/*   Updated: 2024/03/21 17:51:48 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(char *vars, char *error)
{
	ft_putstr_fd("minibing: ", 2);
	if (!vars)
	{
		if (!ft_strcmp(error, "UNCLOSED_QUOTES"))
			ft_putstr_fd("syntax error unclosed quotes\n", 2);
		get_exit_status(unshift_exitcode(2));
		return (2);
	}
	if (!ft_strcmp(error, "NOT_VALID_ID"))
	{
		ft_printf_fd(2, "export: `%s': not a valid identifier\n", vars);
		return (1);
	}
	if (!ft_strcmp(error, "TOO_MANY_ARGS"))
	{
		ft_printf_fd(2, "%s: too many arguments\n", vars);
		return (1);
	}
	if (!ft_strcmp(error, "INVALID_EXIT"))
	{
		ft_printf_fd(2, "exit: %s: numeric argument required\n", vars);
		return (2);
	}
	if (!ft_strcmp(error, "UNEXPECTED_TOKEN"))
	{
		ft_printf_fd(2, "syntax error near unexpected token `%s'\n", vars);
		return (2);
	}
	if (!ft_strcmp(error, "CMD_NOT_FOUND"))
	{
		ft_putstr_fd(vars, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	if (!ft_strcmp(error, "NO_FILE"))
	{
		ft_putstr_fd(vars, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (!ft_strcmp(error, "NO_PERMS"))
	{
		ft_putstr_fd(vars, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	ft_putstr_fd(vars, 2);
	if (!ft_strcmp(error, "IS_DIR"))
	{
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
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
	return ((status | 0xff00) << 8);
}
