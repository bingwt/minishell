/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:58:55 by btan              #+#    #+#             */
/*   Updated: 2024/04/04 15:41:25 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	nl;
	int	len;

	i = 1;
	nl = 1;
	if (!ft_strcmp(args[1], "-n"))
	{
		args++;
		nl--;
	}
	len = ft_strslen(args);
	while (i < len)
	{
		if (i > 1)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	if (nl)
		write(1, "\n", 1);
}
