/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toing.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:44:52 by xlow              #+#    #+#             */
/*   Updated: 2024/04/07 21:02:22 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**strip_args(char **strs)
{
	int		i;
	char	*temp;

	i = 0;
	while (strs[i])
	{
		temp = ft_strip(strs[i], '\a');
		free(strs[i]);
		strs[i] = temp;
		i++;
	}
	return (strs);
}

t_arg	*no_toing(t_arg *args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!args[i].last)
	{
		args[i].cmd = strip_args(args[i].cmd);
		args[i].in = strip_args(args[i].in);
		args[i].out = strip_args(args[i].out);
		i++;
	}
	args[i].cmd = strip_args(args[i].cmd);
	args[i].in = strip_args(args[i].in);
	args[i].out = strip_args(args[i].out);
	return (args);
}
