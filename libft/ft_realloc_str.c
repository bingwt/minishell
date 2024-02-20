/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:50 by xlow              #+#    #+#             */
/*   Updated: 2024/02/20 22:06:46 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_str(char *ptr, size_t size)
{
	size_t		i;
	char		*res;

	i = 0;
	res = ft_calloc(size, 1);
	if (!res)
		return (NULL);
	if (ptr)
	{
		while (ptr[i] && i < size - 1)
		{
			res[i] = ptr[i];
			i++;
		}
		free(ptr);
	}
	return (res);
}
