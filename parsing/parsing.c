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

char	**split_by_space(char *input)
{
	int		i;
	int		j;
	char	c;
	char	*cmd;
	char	**space_split;

	i = 0;
	j = 0;
	cmd = ft_calloc(1, 1);
	while (input[i])
	{
		c = input[i];
		quotes(c);
		if (c == ' ')
		{
			if (!quotes(c) && j > 0)
			{
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
