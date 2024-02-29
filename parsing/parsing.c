/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:10:20 by xlow              #+#    #+#             */
/*   Updated: 2024/02/28 22:07:09 by xlow             ###   ########.fr       */
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

t_arg	*input_parser(char *input)
{
	char	**space_split;
	char	***pipe_split;
	t_arg	*args;

	space_split = NULL;
	pipe_split = NULL;
	input = inject_space(input);
	if (!input)
		return (NULL);
	split_by_space(input, &space_split);
	free(input);
	if (!space_split)
		return (NULL);
	pipe_split = split_by_pipe(space_split);
//	ft_free_split(&space_split);
	if (!pipe_split)
		return (NULL);
	args = rejoin_tokens(pipe_split);
//	ft_free_cubed(&pipe_split);
	if (!args)
		return (NULL);
	return (args);
}

/*
int	main(int argc, char **argv)
{
	(void)argc;
	int	i = 0;
	int j = 0;
	t_arg *args;
	args = input_parser(argv[1]);
	if (!args)
		return (0);
	while (!args[i].last)
	{
		while (args[i].in[j])
		{
			printf("In %d: %s\n", j, args[i].in[j]);
			j++;
		}
		j = 0;
		while (args[i].out[j])
		{
			printf("Out %d: %s\n", j, args[i].out[j]);
			j++;
		}
		j = 0;
		while (args[i].cmd[j])
		{
			printf("Cmd %d: %s\n", j, args[i].cmd[j]);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}*/
