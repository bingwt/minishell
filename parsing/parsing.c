/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:10:20 by xlow              #+#    #+#             */
/*   Updated: 2024/02/27 20:10:21 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*s = argv[1];
	char	**strs;
	int		i = 0;

	(void)argc;
	strs = NULL;
	s = inject_space(s);
	if (!s)
		return (0);
	printf("%s\n", s);
	split_by_space(s, &strs);
	free(s);
	if (!strs)
		return (0);
	while (strs[i])
	{
		printf("Str %d: %s\n", i, strs[i]);
		i++;
	}
	ft_free_split(&strs);
	return (0);
}
/*
char	**split_by_pipe(char **cmds)
{
	int	i;
	int	cmd_idx;

	if (valid_pipes(cmds))
	{
	}
	ft_free_split(&cmds);
*/

/*
char	**input_parser(char *input)
{
	char	*in;
	char	**space_split;
	char	***pipe_split;

	in = input;
	space_split = NULL;
	pipe_split = NULL;
	in = inject_spaces(input);
	if (!in)
		return (NULL);
	split_by_space(in, &space_split);
	free(in);
	if (!space_split)
		return (NULL);
	pipe_split = split_by_pipes(space_split);
	ft_free_split(&space_split);
	if (!pipe_split)
		return (NULL);
}*/
