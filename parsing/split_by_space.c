/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:47:50 by xlow              #+#    #+#             */
/*   Updated: 2024/02/23 22:21:22 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes(char c, char *reset)
{
	static int	squote = 0;
	static int	dquote = 0;

	if (!reset)
	{
		if (c == '\0')
		{
			if (squote)
				return (1);
			if (dquote)
				return (2);
		}
		if (c == '\'' && !dquote)
			squote = !squote;
		if (c == '\"' && !squote)
			dquote = !dquote;
		return (squote | dquote);
	}
	else if (squote || dquote)
	{
		squote = 0;
		dquote = 0;
		return (1);
	}
	return (0);
}

char	*cmd_assign(char *cmd, int *j, char input)
{
	cmd = ft_realloc(cmd, *j + 1, *j + 2);
	cmd[(*j)++] = input;
	return (cmd);
}

char	**split_assign(char **split, int *cmd_idx, char *insert)
{
	split = ft_realloc(split, *cmd_idx * 8, (*cmd_idx + 1) * 8);
	split[(*cmd_idx)++] = insert;
	return (split);
}

char	**split_by_space(char *input)
{
	int		q;
	int		j;
	int		cmd_idx;
	char	*cmd;
	char	**split;

	q = 0;
	j = 0;
	cmd_idx = 0;
	cmd = ft_calloc(1, 1);
	split = NULL;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			q = quotes(*input, NULL);
			if ((quotes('\0', NULL) == 1 && *input == '\"')
				|| (quotes('\0', NULL) == 2 && *input == '\''))
				cmd = cmd_assign(cmd, &j, *input);
		}
		else if (*input == ' ')
		{
			if (!q && j > 0)
			{
				split = split_assign(split, &cmd_idx, cmd);
				cmd = ft_calloc(1, 1);
				j = 0;
			}
			else if (q)
				cmd = cmd_assign(cmd, &j, *input);
		}
		else
			cmd = cmd_assign(cmd, &j, *input);
		input++;
	}
	if (quotes('\0', "reset"))
	{
		split = split_assign(split, &cmd_idx, NULL);
		ft_free_split(&split);
		free(cmd);
		perror("quotes unclosed");
		return (NULL);
	}
	if (j)
		split = split_assign(split, &cmd_idx, cmd);
	else
		free(cmd);
	split = split_assign(split, &cmd_idx, NULL);
	return (split);
}

int	main(int argc, char **argv)
{
	(void)	argc;
	char	**s;
	int		i = 0;

	s = split_by_space(argv[1]);
	if (s)
	{
		while (s[i])
		{
			printf("Str %d: %s\n", i, s[i]);
			i++;
		}
	}
	ft_free_split(&s);
	return (0);
}
/*
char	**input_parser(char *input)
{
	char	*in;
	char	**space_split;
	char	**pipe_split;

	if (!input)
		return (NULL);
	in = input;
	space_split = split_by_space(in);
	pipe_split = split_by_pipes(space_split);
}
*/
