/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:47:50 by xlow              #+#    #+#             */
/*   Updated: 2024/02/28 21:38:06 by xlow             ###   ########.fr       */
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
		if (c == '"' && !squote)
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

void	cmd_assign(t_string *cmd, char input)
{
	cmd->s = ft_realloc(cmd->s, cmd->i + 1, cmd->i + 2);
	cmd->s[cmd->i++] = input;
}

char	**split_assign(char **split, int *cmd_idx, char *insert)
{
	split = ft_realloc(split, *cmd_idx * 8, (*cmd_idx + 1) * 8);
	split[(*cmd_idx)++] = insert;
	return (split);
}

void	handle_space(t_string *cmd, char ***split, int *cmd_idx, int q)
{
	if (!q && cmd->i > 0)
	{
		*split = split_assign(*split, cmd_idx, cmd->s);
		cmd->s = ft_calloc(1, 1);
		cmd->i = 0;
	}
	else if (q)
		cmd_assign(cmd, ' ');
}

char	**cleanup_space(t_string *cmd, char ***split, int *cmd_idx)
{
	if (cmd->i)
		*split = split_assign(*split, cmd_idx, cmd->s);
	else
		free(cmd->s);
	*split = split_assign(*split, cmd_idx, NULL);
	return (*split);
}
/*
void	split_by_space(char *input, char ***split)
{
	int			q;
	int			cmd_idx;
	t_string	cmd;

	q = 0;
	cmd.i = 0;
	cmd_idx = 0;
	cmd.s = ft_calloc(1, 1);
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			q = quotes(*input, NULL);
			if ((quotes('\0', NULL) == 1 && *input == '\"')
				|| (quotes('\0', NULL) == 2 && *input == '\''))
				cmd_assign(&cmd, *input);
		}
		else if (*input == ' ')
			handle_space(&cmd, split, &cmd_idx, q);
		else
			cmd_assign(&cmd, *input);
		input++;
	}
	cleanup_space(&cmd, split, &cmd_idx);
}

int	main(int argc, char **argv)
{
	(void)	argc;
	char	**s;
	int		i = 0;

	s = NULL;
	split_by_space(argv[1], &s);
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

char	**input_parser(char *input)
{
	char	*in;
	char	**space_split;
	char	**pipe_split;

	if (!input)
		return (NULL);
	in = input;
	space_split = NULL;
	split_by_space(in, &space_split);
	pipe_split = split_by_pipes(space_split);
}
*/
