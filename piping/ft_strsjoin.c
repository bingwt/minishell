/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:35:59 by btan              #+#    #+#             */
/*   Updated: 2024/03/08 13:08:11 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcat(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_strsjoin(char **strs)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = ft_strslen(strs);
	len = 0;
	while (i--)
		len += ft_strlen(strs[i]);
	str = ft_calloc(len + 1, sizeof(char *));
	len = ft_strslen(strs);
	i = 0;
	while (i < len)
	{
		ft_strcat(str, strs[i]);
		i++;
	}
	return (str);
}
//
//int	main()
//{
//	char	**strs;
//	char	*str;
//
//	strs = ft_split("This is a test", ' ');
//	str = ft_strsjoin(strs);
//	printf("%s\n", str);
//}
