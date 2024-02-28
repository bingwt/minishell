/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rejoin_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:51:29 by xlow              #+#    #+#             */
/*   Updated: 2024/02/28 22:13:13 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_arg	init_t_arg(void)
{
	t_arg	arg;

	arg.last = 0;
	arg.in_i = 0;
	arg.out_i = 0;
	arg.cmd_i = 0;
	arg.in = NULL;
	arg.out = NULL;
	arg.cmd = NULL;
	return (arg);
}

static void	combine_redir(t_arg *args, char **in, int *i)
{
	if (!ft_strcmp(in[*i], "<") || !ft_strcmp(in[*i], "<<"))
	{
		args->in = split_assign(args->in, &args->in_i, ft_strdup(in[*i]));
		(*i)++;
		args->in_i++;
		args->in = split_assign(args->in, &args->in_i, ft_strdup(in[*i]));
	}
	if (!ft_strcmp(in[*i], ">") || !ft_strcmp(in[*i], ">>"))
	{
		args->out = split_assign(args->out, &args->out_i, ft_strdup(in[*i]));
		(*i)++;
		args->out_i++;
		args->out = split_assign(args->out, &args->out_i, ft_strdup(in[*i]));
	}
	(*i)++;
}

t_arg	*rejoin_tokens(char ***in)
{
	int		i;
	int		a;
	t_arg	*args;

	i = 0;
	a = -1;
	args = ft_calloc(ft_cubelen(in) + 1, sizeof(t_arg));
	while (in[++a])
	{
		while (in[a][i])
		{
			args[a] = init_t_arg();
			if (!ft_strcmp(in[a][i], "<") || !ft_strcmp(in[a][i], "<<") ||
				!ft_strcmp(in[a][i], ">") || !ft_strcmp(in[a][i], ">>"))
				combine_redir(&args[a], in[a], &i);
			else
				args[a].cmd = split_assign(args[a].cmd, &args[a].cmd_i, in[a][i]);
			i++;
		}
		args[a].in = split_assign(args[a].in, &args[a].in_i, NULL);
		args[a].out = split_assign(args[a].out, &args[a].out_i, NULL);
		args[a].cmd = split_assign(args[a].cmd, &args[a].cmd_i, NULL);
	}
	args[a].last = 1;
	return (args);
}
