/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:10:20 by xlow              #+#    #+#             */
/*   Updated: 2024/04/07 20:40:55 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quotes(t_string *cmd, char input)
{
	int	q;

	q = quotes(input, NULL);
	if (!quotes('\0', NULL))
		cmd_assign(cmd, '\a');
	if ((quotes('\0', NULL) == 1 && input == '\"')
		|| (quotes('\0', NULL) == 2 && input == '\''))
		cmd_assign(cmd, input);
	return (q);
}

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
			q = handle_quotes(&cmd, *input);
		else if (ft_iswhitespace(*input))
			handle_space(&cmd, split, &cmd_idx, q);
		else
			cmd_assign(&cmd, *input);
		input++;
	}
	quotes('\0', "reset");
	cleanup_space(&cmd, split, &cmd_idx);
}

static void	free_pipe_split(char ***pipe_split)
{
	int	i;

	i = 0;
	while (pipe_split[i])
	{
		free(pipe_split[i]);
		i++;
	}
	free(pipe_split);
}

t_arg	*input_parser(char *input)
{
	char	**space_split;
	char	***pipe_split;
	t_arg	*args;

	if (!input || !*input)
		return (NULL);
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
	free(space_split);
	if (!pipe_split)
		return (NULL);
	args = rejoin_tokens(pipe_split);
	free_pipe_split(pipe_split);
	if (!args)
		return (NULL);
	args = heredoc_order(args);
	return (args);
}

void	free_args(t_arg *args)
{
	int	i;

	i = 0;
	while (!args[i].last)
	{
		ft_free_split(&args[i].in);
		ft_free_split(&args[i].out);
		ft_free_split(&args[i].cmd);
		i++;
	}
	ft_free_split(&args[i].in);
	ft_free_split(&args[i].out);
	ft_free_split(&args[i].cmd);
	free(args);
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
		printf("Heredoc order for %d, %d", i, args[i].heredoc);
		j = 0;
		i++;
	}
	printf("Heredoc order for %d, %d", i, args[i].heredoc);
	free_args(args);
	return (0);
}
*/
