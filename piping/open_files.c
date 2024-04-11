/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:39:20 by xlow              #+#    #+#             */
/*   Updated: 2024/04/08 22:19:10 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_in(t_arg *args, int *hd_fd)
{
	int	i;
	int	file;

	i = 0;
	while (i < args->in_i - 1)
	{
		if (!ft_strcmp(args->in[i++], "<"))
		{
			file = open(args->in[i++], O_RDONLY);
			if (file == -1)
			{
				if (is_dir(args->in[i - 1]))
					handle_error(args->in[i - 1], NO_PERMS_OPEN);
				else
					handle_error(args->in[i - 1], NO_FILE);
				args->io[1] = -1;
				break ;
			}
			else
				dup2(file, args->io[0]);
		}
		else
			*args = open_heredoc(*args, i++, hd_fd);
	}
}

static void	open_out(t_arg *args)
{
	int	i;
	int	file;

	i = 0;
	while (i < args->out_i - 1)
	{
		if (!ft_strcmp(args->out[i++], ">>"))
			file = open(args->out[i++], APPEND, 0644);
		else
			file = open(args->out[i++], TRUNC, 0644);
		if (file == -1)
		{
			if (!access(args->out[i - 1], F_OK))
				handle_error(args->out[i - 1], NO_PERMS_OPEN);
			else
				handle_error(args->out[i - 1], NO_FILE);
			args->io[1] = -1;
			break ;
		}
		else
			dup2(file, args->io[1]);
	}
}

t_arg	open_files(t_arg args, int *hd_fd)
{
	open_out(&args);
	open_in(&args, hd_fd);
	return (args);
}
