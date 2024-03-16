/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:21:46 by btan              #+#    #+#             */
/*   Updated: 2024/03/17 02:23:39 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_exit(char *str)
{
	int		status;

	if (ft_isdigit(*str) || *str == '-' || *str == '+')
		status = ft_atoi(str);
	else
	{
		handle_error(str, "INVALID_EXIT");
		exit(2);
	}
	if (str[intlen(status)] && !ft_isdigit(str[intlen(status)]))
	{
		handle_error("exit", "TOO_MANY_ARGS");
		exit(1);
	}
	exit(status);
}
