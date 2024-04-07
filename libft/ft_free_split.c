/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:17:33 by xlow              #+#    #+#             */
/*   Updated: 2024/04/07 20:22:37 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	if (!split || !*split)
		return ;
	while ((*split)[i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}
