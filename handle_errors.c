/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:51:59 by btan              #+#    #+#             */
/*   Updated: 2024/04/07 14:47:41 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_status(t_errors error)
{
	if (error == NOT_VALID_ID || error == TOO_MANY_ARGS \
		|| error == NO_PERMS_OPEN || error == NO_FILE)
		return (1);
	if (error == UNCLOSED_QUOTES || error == INVALID_EXIT \
		|| error == UNEXPECTED_TOKEN || error == CMD_NOT_FOUND)
		return (2);
	if (error == NO_PERMS_EXEC || error == IS_DIR)
		return (126);
	if (error == CMD_NOT_FOUND || error == NO_FILE_EXEC)
		return (127);
	return (0);
}

int	handle_error(char *vars, t_errors error)
{
	int	status;

	status = handle_status(error);
	ft_putstr_fd("minibing: ", 2);
	if (error == NOT_VALID_ID)
		ft_printf_fd(2, "export: `%s': not a valid identifier\n", vars);
	if (error == TOO_MANY_ARGS)
		ft_printf_fd(2, "%s: too many arguments\n", vars);
	if (error == UNCLOSED_QUOTES)
		ft_putstr_fd("syntax error unclosed quotes\n", 2);
	if (error == INVALID_EXIT)
		ft_printf_fd(2, "exit: %s: numeric argument required\n", vars);
	if (error == UNEXPECTED_TOKEN)
		ft_printf_fd(2, "syntax error near unexpected token `%s'\n", vars);
	if (error == NO_PERMS_OPEN || error == NO_PERMS_EXEC)
		ft_printf_fd(2, "%s: Permission denied\n", vars);
	if (error == IS_DIR)
		ft_printf_fd(2, "%s: Is a directory\n", vars);
	if (error == NO_FILE || error == NO_FILE_EXEC)
		ft_printf_fd(2, "%s: No such file or directory\n", vars);
	if (error == CMD_NOT_FOUND)
		ft_printf_fd(2, "%s: command not found\n", vars);
	get_exit_status(unshift_exitcode(status));
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
