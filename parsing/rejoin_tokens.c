/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rejoin_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:51:29 by xlow              #+#    #+#             */
/*   Updated: 2024/04/04 19:45:14 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	init_t_arg(void)
{
	t_arg	arg;

	arg.last = 0;
	arg.in_i = 0;
	arg.out_i = 0;
	arg.cmd_i = 0;
	arg.heredoc = 0;
	arg.io[0] = dup(0);
	arg.io[1] = dup(1);
	arg.in = NULL;
	arg.out = NULL;
	arg.cmd = NULL;
	return (arg);
}

static void	combine_redir(t_arg *arg, char **in, int *i)
{
	if (!ft_strcmp(in[*i], "<") || !ft_strcmp(in[*i], "<<"))
	{
		arg->in = split_assign(arg->in, &arg->in_i, in[*i]);
		(*i)++;
		arg->in = split_assign(arg->in, &arg->in_i, in[*i]);
	}
	if (!ft_strcmp(in[*i], ">") || !ft_strcmp(in[*i], ">>"))
	{
		arg->out = split_assign(arg->out, &arg->out_i, in[*i]);
		(*i)++;
		arg->out = split_assign(arg->out, &arg->out_i, in[*i]);
	}
}

t_arg	*heredoc_order(t_arg *args)
{
	int	i;
	int	j;
	int	first;

	first = 0;
	i = 0;
	j = -1;
	while (!args[i].last)
	{
		while (++j < args[i].in_i)
		{
			if (!ft_strcmp(args[i].in[j], "<<"))
			{
				if (first)
					args[i].heredoc = 1;
				first = 1;
				break ;
			}
		}
		j = -1;
		i++;
	}
	while (++j < args[i].in_i)
		if (!ft_strcmp(args[i].in[j], "<<") && first)
			args[i].heredoc = 1;
	return (args);
}

/*
static void	combine_redir(t_arg *arg, char **in, int *i)
{
	if (!ft_strcmp(in[*i], "<") || !ft_strcmp(in[*i], "<<"))
	{
		arg->in = split_assign(arg->in, &arg->in_i, ft_strdup(in[*i]));
		(*i)++;
		arg->in = split_assign(arg->in, &arg->in_i, ft_strdup(in[*i]));
	}
	if (!ft_strcmp(in[*i], ">") || !ft_strcmp(in[*i], ">>"))
	{
		arg->out = split_assign(arg->out, &arg->out_i, ft_strdup(in[*i]));
		(*i)++;
		arg->out = split_assign(arg->out, &arg->out_i, ft_strdup(in[*i]));
	}
}
*/

t_arg	*rejoin_tokens(char ***in)
{
	int		i;
	int		a;
	t_arg	*arg;

	i = -1;
	a = -1;
	arg = ft_calloc(ft_cubelen(in) + 1, sizeof(t_arg));
	while (in[++a])
	{
		arg[a] = init_t_arg();
		while (in[a][++i])
		{
			if (!ft_strcmp(in[a][i], "<") || !ft_strcmp(in[a][i], "<<") ||
				!ft_strcmp(in[a][i], ">") || !ft_strcmp(in[a][i], ">>"))
				combine_redir(&arg[a], in[a], &i);
			else
				arg[a].cmd = split_assign(arg[a].cmd, &arg[a].cmd_i, in[a][i]);
		}
		arg[a].in = split_assign(arg[a].in, &arg[a].in_i, NULL);
		arg[a].out = split_assign(arg[a].out, &arg[a].out_i, NULL);
		arg[a].cmd = split_assign(arg[a].cmd, &arg[a].cmd_i, NULL);
		i = -1;
	}
	arg[a - 1].last = 1;
	return (arg);
}
