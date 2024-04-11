/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:21:46 by btan              #+#    #+#             */
/*   Updated: 2024/04/11 16:33:27 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (handle_error(arg, INVALID_EXIT));
	}
	return (0);
}

void	ft_exit(t_arg *arg, int i, t_list **envll)
{
	char	**args;
	int		status;

	args = arg[i].cmd;
	printf("exit\n");
	if (!args[1])
	{
		free_args(arg);
		ft_lstclear(envll, free);
		exit(get_exit_status(-1));
	}
	if (ft_isalnum(args[1][0]) || args[1][0] == '-' || args[1][0] == '+')
	{
		if (valid_arg(args[1]))
			return ;
		status = ft_atoi(args[1]);
	}
	if (args[2])
	{
		handle_error(args[0], TOO_MANY_ARGS);
		return ;
	}
	free_args(arg);
	ft_lstclear(envll, free);
	exit(status);
}
