/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:10:16 by xlow              #+#    #+#             */
/*   Updated: 2024/02/27 20:10:17 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_redir(char *input)
{
	int	i;

	i = 1;
	if (!ft_strncmp(input, "<<<", 3) || !ft_strncmp(input, ">>>", 3))
		return (0);
	if (!ft_strncmp(input, "<>", 2) || !ft_strncmp(input, "><", 2))
		return (0);
	while (input[i] == ' ')
		i++;
	if (i > 1 && (input[i] == '<' || input[i] == '>'))
		return (0);
	if (input[i] == '\0')
		return (0);
	return (1);
}

static void	assign_meta(t_string *res, int q, char curr, char next)
{
	if (!q && (curr == '<' || curr == '>' || curr == '|')
		&& next != '<' && next != '>')
	{
		cmd_assign(res, curr);
		cmd_assign(res, ' ');
	}
	else if (!q && curr != '<' && curr != '>' && curr != '|'
		&& (next == '<' || next == '>' || next == '|'))
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
		if ((input[i] == '<' || input[i] == '>') && !valid_redir(input + i))
		{
			free(res.s);
			perror("invalid redirect");
			return (NULL);
		}
		assign_meta(&res, q, input[i], input[i + 1]);
	}
	if (quotes('\0', "reset"))
	{
		free(res.s);
		perror("unclosed quotes");
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
