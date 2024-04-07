/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:15:39 by xlow              #+#    #+#             */
/*   Updated: 2024/04/07 20:39:27 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strip(char *s, char c)
{
	int			i;
	t_string	res;

	i = 0;
	res.i = 0;
	if (!s)
		return (NULL);
	res.s = ft_calloc(1, 1);
	while (s[i])
	{
		if (s[i] != c)
		{
			res.s = ft_realloc(res.s, res.i + 1, res.i + 2);
			res.s[res.i] = s[i];
			res.i++;
		}
		i++;
	}
	return (res.s);
}
