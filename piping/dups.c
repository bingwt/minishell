/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:13:10 by xlow              #+#    #+#             */
/*   Updated: 2024/03/18 19:24:15 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	*dup_first(t_arg *args, int *new, int i, int *hd_fd)
{
	dup2(new[1], args[i].io[1]);
	args[i] = open_files(args[i], hd_fd);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	close(new[0]);
	close(new[1]);
	return (args);
}

static t_arg	*dup_last(t_arg *args, int old, int i, int *hd_fd)
{
	dup2(old, args[i].io[0]);
	args[i] = open_files(args[i], hd_fd);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	return (args);
}

static t_arg	*dup_middle(t_arg *args, int *new, int i, int *hd_fd)
{
	dup2(new[2], args[i].io[0]);
	dup2(new[1], args[i].io[1]);
	args[i] = open_files(args[i], hd_fd);
	dup2(args[i].io[0], STDIN_FILENO);
	dup2(args[i].io[1], STDOUT_FILENO);
	close(new[0]);
	return (args);
}

t_arg	*child_dup(t_arg *args, int *new_fd, int i, int *hd_fd)
{
	if (!i)
		args = dup_first(args, new_fd, i, hd_fd);
	else if (args[i].last)
		args = dup_last(args, new_fd[2], i, hd_fd);
	else
		args = dup_middle(args, new_fd, i, hd_fd);
	return (args);
}
