/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cubed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:31 by xlow              #+#    #+#             */
/*   Updated: 2024/04/07 20:22:31 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_cubed(char ****cube)
{
	int	i;

	i = 0;
	if (!cube || !*cube)
		return ;
	while ((*cube)[i])
	{
		ft_free_split(&(*cube)[i]);
		i++;
	}
	free(*cube);
	*cube = NULL;
}
