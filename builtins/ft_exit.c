/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:21:46 by btan              #+#    #+#             */
/*   Updated: 2024/03/17 01:46:56 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *str)
{
	int		status;

	if (ft_isdigit(*str) || *str == '-' || *str == '+')
		status = ft_atoi(str);
	else
	{
		handle_error(str, "INVALID_EXIT");
		status = 2;
	}
	printf("exit\n");
	exit(status);
}
