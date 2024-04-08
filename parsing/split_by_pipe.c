/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:00:11 by xlow              #+#    #+#             */
/*   Updated: 2024/04/08 15:49:31 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_input(char **in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		free(in[i]);
		i++;
	}
	return (NULL);
}

static int	valid_pipe(char **in)
{
	int	i;

	i = 1;
	if (!ft_strcmp(in[0], "|"))
	{
		handle_error("|", UNEXPECTED_TOKEN);
		return (0);
	}
	while (in[i])
	{
		if (!ft_strcmp(in[i], "|"))
		{
			if (!in[i + 1] || !ft_strcmp(in[i + 1], "|")
				|| ft_strchr(in[i - 1], '>') || ft_strchr(in[i - 1], '<'))
			{
				handle_error("|", UNEXPECTED_TOKEN);
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

static void	new_cmd_pipe(char ***cmd, int *c, char ***res)
{
	*cmd = split_assign(*cmd, c, NULL);
	*res = *cmd;
	*cmd = ft_calloc(1, 8);
	(*c) = 0;
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
	if (!valid_pipe(in) || !valid_redir(in))
		return (free_input(in));
	cmd = NULL;
	res = ft_calloc(count_pipe(in) + 2, 8);
	res[count_pipe(in) + 1] = NULL;
	while (in[i])
	{
		cmd = split_assign(cmd, &c, in[i++]);
		if (!in[i] || (in[i] && !ft_strcmp(in[i], "|")))
			new_cmd_pipe(&cmd, &c, &(res[r++]));
		if (in[i] && !ft_strcmp(in[i], "|"))
			free(in[i++]);
	}
	free(cmd);
	return (res);
}

/*
int	main(void)
{
	char	***piped;
	char	*in[] = {"<", "infile", "cat", ">", "outfile", "-e",
					"|", "<<", "eof", "cat", ">", "outfile2", NULL};
	piped = split_by_pipe(in);
	int	i = 0;
	int n = 0;
	while (piped[i])
	{
		while (piped[i][n])
		{
			printf("%s\n", piped[i][n]);
			n++;
		}
		n = 0;
		i++;
	}
	return (0);
}
*/
