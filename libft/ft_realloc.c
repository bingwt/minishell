/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:06 by xlow              #+#    #+#             */
/*   Updated: 2024/04/07 20:22:07 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*res;

	if (!new_size)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_calloc(new_size, 1));
	res = ft_calloc(new_size, 1);
	if (!res)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(res, ptr, old_size);
	free(ptr);
	return (res);
}

/*
int	main(void)
{
	char	**split;
	char	*s1 = "b";
	char	*s2 = "o";
	char	*s3 = "p";
	int		i = 0;

	split = malloc(sizeof(char *) * 3);
	split[0] = s1, split[1] = s2; split[2] = NULL;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	split = ft_realloc(split, 16, 32);
	apparently doesnt matter if oldsize 16 or 24
	i = 0;
	split[2] = s3, split[3] = NULL;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	free(split);
	return (0);
}*/
