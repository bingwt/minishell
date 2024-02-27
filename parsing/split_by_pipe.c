/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:00:11 by xlow              #+#    #+#             */
/*   Updated: 2024/02/27 21:06:22 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	valid_pipe(char **in)
{
	int	i;

	i = 1;
	if (!ft_strcmp(in[0], "|"))
		return (0);
	while (in[i])
	{
		if (!ft_strcmp(in[i], "|"))
		{
			if (!in[i + 1] || ft_strcmp(in[i], "|")
				|| ft_strchr(in[i - 1], '>') || ft_strchr(in[i - 1], '<'))
			{
				perror("pipe");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	count_pipe(char **in)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (in[i])
	{
		if (!ft_strcmp(in[i], "|"))
			res++;
		i++;
	}
	return (res);
}

char	***split_by_pipe(char **in)
{
	int		i;
	int		c;
	int		r;
	char	**cmd;
	char	***res;

	i = 0;
	c = 0;
	r = 0;
	if (!valid_pipe(in))
		return (NULL);
	cmd = NULL;
	res = ft_calloc(count_pipe(in) + 2, 8);
	if (!res)
		return (NULL);
	res[count_pipe(in) + 1] = NULL;
	while (in[i])
	{
		cmd = split_assign(cmd, &c, in[i]);
		i++;
		if (!ft_strcmp(in[i], "|"))
		{
			res[r] = cmd;
			r++;
			cmd = ft_calloc(1, 8);
			c = 0;
			i++;
		}
	}
	return (res);
}
