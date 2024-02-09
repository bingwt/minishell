/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:25:03 by btan              #+#    #+#             */
/*   Updated: 2024/02/09 15:34:50 by btan             ###   ########.fr       */
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

void	ft_cd(const char *path)
{
	chdir(path);
}

char	*ft_pwd(void)
{
	char	*path;

	path = malloc(PATH_MAX + 1 * (sizeof(char)));
	if (!path)
		return (NULL);
	path[PATH_MAX] = '\0';
	getcwd(path, PATH_MAX);
	//printf("%s\n", path);
	//free(path);
	return (path);
}
