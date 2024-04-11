/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:44 by xlow              #+#    #+#             */
/*   Updated: 2024/04/08 18:24:45 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *path)
{
	struct stat	s_statbuf;

	if (stat(path, &s_statbuf))
		return (0);
	return (S_ISDIR(s_statbuf.st_mode));
}

void	dir_check(t_arg *args, int i)
{
	if (!access(args[i].cmd[0], F_OK))
	{
		if (is_dir(args[i].cmd[0]))
			exit(handle_error(args[i].cmd[0], IS_DIR));
		else
			exit(handle_error(args[i].cmd[0], NO_PERMS_EXEC));
	}
	else
		exit(handle_error(args[i].cmd[0], NO_FILE_EXEC));
}
