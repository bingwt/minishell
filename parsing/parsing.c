/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:47:50 by xlow              #+#    #+#             */
/*   Updated: 2024/02/21 21:12:46 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		quotes(char c)
{
	static int	squote = 0;
	static int	dquote = 0;

	if (c == '\0')
	{
		if (squote)
		{
			squote = !squote;
			return (1);
		}
		if (dquote)
		{
			dquote = !dquote;
			return (2);
		}
	}
	if (c == '\'' && !dquote)
		squote = !squote;
	if (c == '\"' && !squote)
		dquote = !dquote;
	return (squote | dquote);
}

char	**split_by_space(char *input)
{
	int		i;
	int		j;
	int		cmd_idx;
	char	*cmd;
	char	**space_split;

	i = 0;
	j = 0;
	cmd_idx = 0;
	cmd = ft_calloc(1, 1);
	space_split = NULL;
	while (input[i])
	{
		quotes(input[i]); // find a way print literal quotes
		if (input[i] == ' ')
		{
			if (!quotes(input[i]) && j > 0)
			{
				space_split = ft_realloc(space_split, cmd_idx * 8, (cmd_idx + 1) * 8);
				space_split[cmd_idx++] = cmd;
				cmd = ft_calloc(1, 1);
				j = 0;
			}
			else
			{
				cmd = ft_realloc(cmd, j + 1, j + 2); // pls test dis
				cmd[j] = input[i];
			}
		}
		else // control with else ifs and else after settling quotes
		{
			cmd = ft_realloc(cmd, j + 1, j + 2);
			cmd[j] = input[i];
		}
	}
	if (j)
	{
		space_split = ft_realloc(space_split, cmd_idx * 8, (cmd_idx + 1) * 8);
		space_split[cmd_idx++] = cmd;
	}
	else
		free(cmd);
	space_split = ft_realloc(space_split, cmd_idx * 8, (cmd_idx + 1) * 8);
	space_split[cmd_idx] = NULL;
	if (quotes('\0'))
	{
		ft_free_split(&space_split);
		perror("quotes unclosed");
		return (NULL);
	}
	return (space_split);
}

char	**input_parser(char *input)
{
	char	**space_split;
	char	**pipe_split;

	if (!input)
		return (NULL);
	space_split = split_by_space(input);
	pipe_split = split_by_pipes(space_split);
}
