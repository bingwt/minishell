/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:58:55 by btan              #+#    #+#             */
/*   Updated: 2024/03/21 02:05:10 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strslen(args);
	while (i < len)
	{
		if (i > 0)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	write(1, "\n", 1);
}
