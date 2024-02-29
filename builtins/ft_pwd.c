/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:59:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/28 14:00:02 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(void)
{
	char	*path;

	path = malloc(PATH_MAX + 1 * (sizeof(char)));
	if (!path)
		return (NULL);
	path[PATH_MAX] = '\0';
	getcwd(path, PATH_MAX);
	return (path);
}