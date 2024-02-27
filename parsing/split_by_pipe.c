/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:00:11 by xlow              #+#    #+#             */
/*   Updated: 2024/02/27 21:06:22 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	valid_pipe(char **in)
{
	int	i;

	i = 1;
	if (!ft_strcmp(in[0], "|"))
		return (0);
	while (in[i])
	{
		if (!ft_strcmp(in[i], "|"))
		{
			if (!in[i + 1] || ft_strcmp(in[i], "|")
				|| ft_strchr(in[i - 1], '>') || ft_strchr(in[i - 1], '<'))
			{
				perror("pipe");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

char	**rejoin_cmds(char **in)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = NULL;
