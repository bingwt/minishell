/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:10:16 by xlow              #+#    #+#             */
/*   Updated: 2024/04/08 15:51:20 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_redir(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_strcmp(input[i], "<<<") || !ft_strcmp(input[i], ">>>"))
			return (0);
		if (!ft_strcmp(input[i], "<>") || !ft_strcmp(input[i], "><"))
			return (0);
		i++;
	}
	return (1);
}

static void	assign_meta(t_string *res, int q, char curr, char next)
{
	if (!q && (curr == '<' || curr == '>')
		&& next != '<' && next != '>')
	{
		cmd_assign(res, curr);
		cmd_assign(res, ' ');
	}
	else if (!q && curr != '<' && curr != '>'
		&& (next == '<' || next == '>' || next == '|'))
	{
		cmd_assign(res, curr);
		cmd_assign(res, ' ');
	}
	else if (!q && curr == '|')
	{
		cmd_assign(res, curr);
		cmd_assign(res, ' ');
	}
	else
		cmd_assign(res, curr);
}

char	*inject_space(char *input)
{
	int			i;
	int			q;
	t_string	res;

	i = -1;
	res.i = 0;
	res.s = ft_calloc(1, 1);
	while (input[++i])
	{
		q = quotes(input[i], NULL);
		assign_meta(&res, q, input[i], input[i + 1]);
	}
	if (quotes('\0', "reset"))
	{
		free(res.s);
		handle_error(NULL, UNCLOSED_QUOTES);
		return (NULL);
	}
	return (res.s);
}

/*
int	main(int argc, char **argv)
{
	(void)argc;
	char	*s;

	s = inject_space(argv[1]);
	if (!s)
		return (0);
	printf("%s\n", s);
	free(s);
	return (0);
}*/
