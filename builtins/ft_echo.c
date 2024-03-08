/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:58:55 by btan              #+#    #+#             */
/*   Updated: 2024/02/28 13:59:04 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(const char *str)
{
	if (!ft_strncmp("-n", str, 2))
		printf("%s", str + 3);
	else
		printf("%s\n", str);
}
